// CopyrightNotice


#include "Units/PlayerUnit.h"

#include "Combat/TurnManager.h"
#include "Grid/TacticalGrid.h"
#include "Grid/TacticalGridTile.h"
#include "Kismet/GameplayStatics.h"



APlayerUnit::APlayerUnit()
{
	PrimaryActorTick.bCanEverTick = true;
	
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

	TurnManager = Cast<ATurnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATurnManager::StaticClass()));
}

void APlayerUnit::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!ensure(TurnManager)) { return; }
	const bool bIsDown = GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::E);
	if (bIsDown && !bEndTurnKeyWasDown && TurnManager->GetActiveUnit() == this)
	{
		TurnManager->RequestEndTurn();
	}
	bEndTurnKeyWasDown = bIsDown;	
}

void APlayerUnit::OnTurnStart()
{
	Super::OnTurnStart();
	bEndTurnKeyWasDown = true;
}


