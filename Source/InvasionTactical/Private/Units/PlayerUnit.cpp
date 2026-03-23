// CopyrightNotice


#include "Units/PlayerUnit.h"

#include "Grid/TacticalGrid.h"
#include "Grid/TacticalGridTile.h"


APlayerUnit::APlayerUnit()
{
	SetFaction(EFaction::Player);
}

void APlayerUnit::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerUnit::OnTurnStart()
{
	Super::OnTurnStart();
}

void APlayerUnit::MoveToTile(ATacticalGridTile* MoveTile)
{
	// TODO: Stepwise movement post-POC, teleport for now
	if (!MoveTile) { return; }
	ConsumeMovementPoints(GetMovementPointsRemaining()); // Consume all movement points for POC
	SetCurrentTile(MoveTile);
	SetActorLocation(FVector(MoveTile->GetActorLocation().X, MoveTile->GetActorLocation().Y, GetActorLocation().Z));
}

void APlayerUnit::Initialise(ATacticalGrid* TacticalGrid, const FMissionSoldier& NewSoldierData)
{
	if (TacticalGrid)
	{
		FIntPoint StartCoords = TacticalGrid->GetGridLocationFromWorld(GetActorLocation());
		if (ATacticalGridTile* StartTile = TacticalGrid->GetTile(StartCoords))
		{
			SetCurrentTile(StartTile);
		}
	}

	SoldierData = NewSoldierData;
	UE_LOG(LogTemp, Log, TEXT("APlayerUnit::Initialise — soldier: %s"), *SoldierData.DisplayName.ToString());
}
