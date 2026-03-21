// CopyrightNotice


#include "GameMode/TacticalGameMode.h"

#include "Combat/CombatManager.h"
#include "Combat/TurnManager.h"
#include "Grid/TacticalGrid.h"
#include "Kismet/GameplayStatics.h"
#include "Units/BaseUnit.h"
#include "Units/EnemyUnit.h"
#include "Units/PlayerUnit.h"
#include "Data/MissionData.h"
#include "GameFramework/PlayerStart.h"
#include "Subsystems/MissionBridgeSubsystem.h"


void ATacticalGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (UWorld* World = GetWorld())
	{
		TacticalGrid = Cast<ATacticalGrid>(UGameplayStatics::GetActorOfClass(World, ATacticalGrid::StaticClass()));
		TurnManager = Cast<ATurnManager>(UGameplayStatics::GetActorOfClass(World, ATurnManager::StaticClass()));
		CombatManager = Cast<ACombatManager>(UGameplayStatics::GetActorOfClass(World, ACombatManager::StaticClass()));
		UMissionBridgeSubsystem* MissionBridgeSubsystem = GetGameInstance()->GetSubsystem<UMissionBridgeSubsystem>();
		
		TArray<FMissionSoldier> Squad = MissionBridgeSubsystem->GetPendingSquad();
		
		if (Squad.IsEmpty())
		{
			for (int32 i = 0; i < 5; i++) { Squad.Add(FMissionSoldier()); }
		}
		SpawnUnits(World, Squad);
				
		MissionBridgeSubsystem->ClearPendingSquad();
		
		TArray<AActor*> DiscoveredUnits;
		UGameplayStatics::GetAllActorsOfClass(World, ABaseUnit::StaticClass(), DiscoveredUnits);
		ExpectedUnitCount = DiscoveredUnits.Num();
		for (ABaseUnit* Unit : Units)
		{
			if (AEnemyUnit* Enemy = Cast<AEnemyUnit>(Unit)) { Enemy->Initialise(TurnManager, CombatManager, TacticalGrid); }
		}
		TryStartCombat();
		TurnManager->OnCombatEnded.AddDynamic(this, &ATacticalGameMode::EndCombat);
	}
}

void ATacticalGameMode::TryStartCombat()
{
	if (ExpectedUnitCount <= 0 || Units.Num() != ExpectedUnitCount) { return; }
	if (!ensure(TurnManager)) { return; }
	TurnManager->StartCombat(Units);
}

void ATacticalGameMode::SpawnUnits(UWorld* World, TArray<FMissionSoldier> Squad)
{
	if (!World || Squad.IsEmpty()) { return; }
	
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);
	
	if (Squad.Num() > PlayerStarts.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Squad size (%d) is larger than number of player starts (%d)"), Squad.Num(), PlayerStarts.Num());
	}
	
	for (int32 i = 0; i < Squad.Num(); i++)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = World->GetFirstPlayerController();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;		
		if (APlayerUnit* PlayerUnit = World->SpawnActor<APlayerUnit>(PlayerUnitClass, PlayerStarts[i]->GetActorLocation(), PlayerStarts[i]->GetActorRotation(), SpawnParams))
		{
			PlayerUnit->Initialise(TacticalGrid, Squad[i]);
		}		
	}		
}

void ATacticalGameMode::EndCombat(const bool bPlayerWon)
{
	FMissionResult MissionResult;
	MissionResult.bIsValid = true;
	MissionResult.bVictory = bPlayerWon;
		
	for (ABaseUnit* Unit : TurnManager->GetPlayerUnits())
	{
		APlayerUnit* PlayerUnit = Cast<APlayerUnit>(Unit);
		if (PlayerUnit && !PlayerUnit->IsAlive())
		{
			MissionResult.CasualtyIDs.Add(PlayerUnit->GetSoldierID());
		}
	}
	MissionResult.CreditsAwarded = bPlayerWon ? 100 : 0;

	UE_LOG(LogTemp, Log, TEXT("ATacticalGameMode::EndCombat — Victory: %s | Casualties: %d | Credits: %d"),
		bPlayerWon ? TEXT("true") : TEXT("false"),
		MissionResult.CasualtyIDs.Num(),
		MissionResult.CreditsAwarded);

	for (const FGuid& ID : MissionResult.CasualtyIDs) 
	{
		UE_LOG(LogTemp, Log, TEXT("  Casualty: %s"), *ID.ToString());
	}

	if (UMissionBridgeSubsystem* MissionBridgeSubsystem = GetGameInstance()->GetSubsystem<UMissionBridgeSubsystem>())
	{
		MissionBridgeSubsystem->SetPendingMissionResult(MissionResult);
	}
	
	UGameplayStatics::OpenLevel(GetWorld(), FName(BaseManagementLevel.GetAssetName()));
}

void ATacticalGameMode::RegisterUnit(ABaseUnit* Unit)
{
	if (!Unit) { return; }

	Units.Add(Unit);
	if (AEnemyUnit* EnemyUnit = Cast<AEnemyUnit>(Unit))
	{
		EnemyUnit->Initialise(TurnManager, CombatManager, TacticalGrid);
	}

	TryStartCombat();
}
