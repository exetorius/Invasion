// CopyrightNotice


#include "Units/PlayerUnit.h"

#include "Grid/TacticalGrid.h"
#include "Grid/TacticalGridTile.h"
#include "Kismet/GameplayStatics.h"


APlayerUnit::APlayerUnit()
{
	SetFaction(EFaction::Player);
}

void APlayerUnit::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Refactor — replace with injection via ATacticalGameMode. BeginPlay caching is a POC shortcut.
	ATacticalGrid* Grid = Cast<ATacticalGrid>(UGameplayStatics::GetActorOfClass(GetWorld(), ATacticalGrid::StaticClass()));
	if (Grid)
	{
		FIntPoint StartCoords = Grid->GetGridLocationFromWorld(GetActorLocation());
		if (ATacticalGridTile* StartTile = Grid->GetTile(StartCoords))
		{
			SetCurrentTile(StartTile);
		}
	}
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
	SetActorLocation(MoveTile->GetActorLocation());
}
