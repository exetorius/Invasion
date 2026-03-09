// CopyrightNotice


#include "Units/EnemyUnit.h"

#include "Combat/CombatManager.h"
#include "Combat/TurnManager.h"
#include "Grid/CoverActor.h"
#include "Grid/TacticalGrid.h"
#include "Grid/TacticalGridTile.h"
#include "Pathfinder.h"
#include "Kismet/GameplayStatics.h"


AEnemyUnit::AEnemyUnit()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetFaction(EFaction::Enemy);
}

void AEnemyUnit::BeginPlay()
{
	Super::BeginPlay();
	
	// TODO: Refactor — replace GetAllActorsOfClass caching with injection via ATacticalGameMode. BeginPlay caching is a POC shortcut.
	TurnManager = Cast<ATurnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATurnManager::StaticClass()));
	CombatManager = Cast<ACombatManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACombatManager::StaticClass()));
	TacticalGrid = Cast<ATacticalGrid>(UGameplayStatics::GetActorOfClass(GetWorld(), ATacticalGrid::StaticClass()));

	if (TacticalGrid)
	{
		FIntPoint StartCoords = TacticalGrid->GetGridLocationFromWorld(GetActorLocation());
		if (ATacticalGridTile* StartTile = TacticalGrid->GetTile(StartCoords))
		{
			SetCurrentTile(StartTile);
		}
	}

}

void AEnemyUnit::OnTurnStart()
{
	Super::OnTurnStart();

	// Guard — ensure refs valid, CurrentTile valid
	if (!ensure(TurnManager) || !ensure(CombatManager) || !ensure(TacticalGrid)) { return; }

	// Find all living player units
	const TArray<ABaseUnit*> LivingPlayers = TurnManager->GetPlayerUnits().FilterByPredicate([](const ABaseUnit* Unit) { return Unit && Unit->IsAlive(); });

	// If none → RequestEndTurn, return
	if (LivingPlayers.IsEmpty())
	{
		TurnManager->RequestEndTurn();
		return;
	}

	// Find visible players (LoS check each)
	const FIntPoint MyCoords = TacticalGrid->GetGridLocationFromWorld(GetActorLocation());
	TArray<ABaseUnit*> VisiblePlayers;

	for (ABaseUnit* Player : LivingPlayers)
	{
		const FIntPoint PlayerCoords = TacticalGrid->GetGridLocationFromWorld(Player->GetActorLocation());
		const int32 ManhattanDist = FMath::Abs(MyCoords.X - PlayerCoords.X) + FMath::Abs(MyCoords.Y - PlayerCoords.Y);

		// Skip if out of shooting range
		if (ManhattanDist > MaxShootRange) { continue; }

		// Skip if obstructed by a wall
		FHitResult WallHit;
		if (GetWorld()->LineTraceSingleByChannel(WallHit, GetActorLocation(), Player->GetActorLocation(), ECC_GameTraceChannel1)) { continue; }

		// Skip if behind full cover
		FHitResult CoverHit;
		if (GetWorld()->LineTraceSingleByChannel(CoverHit, GetActorLocation(), Player->GetActorLocation(), ECC_GameTraceChannel2))
		{
			const ACoverActor* Cover = Cast<ACoverActor>(CoverHit.GetActor());
			if (Cover && Cover->GetCoverType() == ECoverType::Full) { continue; }
		}

		// LoS clear — player is visible
		VisiblePlayers.Add(Player);
	}

	if (!VisiblePlayers.IsEmpty())
	{
		// Pick nearest visible player by Manhattan distance
		// TODO: Target greatest threat / weakest player post-POC
		ABaseUnit* Target = nullptr;
		int32 NearestDist = INT_MAX;
		for (ABaseUnit* Player : VisiblePlayers)
		{
			const FIntPoint PlayerCoords = TacticalGrid->GetGridLocationFromWorld(Player->GetActorLocation());
			const int32 Dist = FMath::Abs(MyCoords.X - PlayerCoords.X) + FMath::Abs(MyCoords.Y - PlayerCoords.Y);
			if (Dist < NearestDist)
			{
				NearestDist = Dist;
				Target = Player;
			}
		}

		if (ensure(Target) && ensure(GetCurrentTile()))
		{
			const FIntPoint TargetCoords = TacticalGrid->GetGridLocationFromWorld(Target->GetActorLocation());

			// Shoot — cover is what the target has facing us
			// TODO: bFlanking always false for POC — wire flank geometry check post-POC
			CombatManager->ResolveHit(this, Target, TacticalGrid->GetCover(TargetCoords, MyCoords), false);

			// Shooting costs half remaining movement (action economy)
			// TODO: Refine — full action/bonus action/reaction system post-POC
			ConsumeMovementPoints(GetMovementPointsRemaining() / 2);

			// Seek cover toward target with remaining movement
			if (GetMovementPointsRemaining() > 0)
			{
				ATacticalGridTile* DestTile = nullptr;
				int32 StepsTaken = 0;
				const TArray<ATacticalGridTile*> Path = TacticalGrid->GetPathfinder()->FindPath(GetCurrentTile(), Target->GetCurrentTile());

				for (ATacticalGridTile* PathTile : Path)
				{
					if (StepsTaken >= GetMovementPointsRemaining()) { break; }
					if (PathTile == GetCurrentTile()) { continue; }
					if (PathTile->IsOccupied()) { break; }

					DestTile = PathTile;
					StepsTaken++;

					// TODO: Cover preference per subclass — hardcoded to first non-None tile for POC
					if (TacticalGrid->GetCover(PathTile->GetGridCoordinates(), TargetCoords) != ECoverType::None) { break; }
				}

				if (DestTile && DestTile != GetCurrentTile())
				{
					// TODO: Stepwise movement with delay — teleport for POC, animation post-POC
					ConsumeMovementPoints(StepsTaken);
					SetCurrentTile(DestTile);
					SetActorLocation(DestTile->GetActorLocation());
				}
			}
		}
	}
	else
	{
		// No visible target — pathfind to the nearest reachable player, advance + prefer cover
		if (!ensure(GetCurrentTile()))
		{
			TurnManager->RequestEndTurn();
			return;
		}

		// Run FindPath to each living player, take the shortest
		TArray<ATacticalGridTile*> ShortestPath;
		ABaseUnit* NearestPlayer = nullptr;
		for (ABaseUnit* Player : LivingPlayers)
		{
			if (!Player->GetCurrentTile()) { continue; }

			TArray<ATacticalGridTile*> Path = TacticalGrid->GetPathfinder()->FindPath(GetCurrentTile(), Player->GetCurrentTile());
			if (Path.IsEmpty()) { continue; }

			if (ShortestPath.IsEmpty() || Path.Num() < ShortestPath.Num())
			{
				ShortestPath = Path;
				NearestPlayer = Player;
			}
		}

		if (!ShortestPath.IsEmpty() && ensure(NearestPlayer))
		{
			const FIntPoint NearestPlayerCoords = TacticalGrid->GetGridLocationFromWorld(NearestPlayer->GetActorLocation());

			// Advance along path — stop at first covered tile within movement range
			// TODO: Cover preference per subclass — hardcoded to first non-None tile for POC
			ATacticalGridTile* DestTile = nullptr;
			int32 StepsTaken = 0;

			for (ATacticalGridTile* PathTile : ShortestPath)
			{
				if (StepsTaken >= GetMovementPointsRemaining()) { break; }
				if (PathTile == GetCurrentTile()) { continue; }
				if (PathTile->IsOccupied()) { break; }

				DestTile = PathTile;
				StepsTaken++;

				if (TacticalGrid->GetCover(PathTile->GetGridCoordinates(), NearestPlayerCoords) != ECoverType::None) { break; }
			}

			if (DestTile && DestTile != GetCurrentTile())
			{
				// TODO: Stepwise movement with delay — teleport for POC, animation post-POC
				ConsumeMovementPoints(StepsTaken);
				SetCurrentTile(DestTile);
				SetActorLocation(DestTile->GetActorLocation());
			}
		}
	}

	TurnManager->RequestEndTurn();
}
