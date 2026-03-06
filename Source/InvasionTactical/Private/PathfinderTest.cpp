// CopyrightNotice


#include "PathfinderTest.h"

#include "Pathfinder.h"
#include "Grid/TacticalGrid.h"
#include "Grid/TacticalGridTile.h"
#include "Kismet/GameplayStatics.h"


APathfinderTest::APathfinderTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APathfinderTest::BeginPlay()
{
	Super::BeginPlay();
	
	ATacticalGrid* TacticalGrid = Cast<ATacticalGrid>(UGameplayStatics::GetActorOfClass(GetWorld(), ATacticalGrid::StaticClass()));
	
	if (!ensure(TacticalGrid)) { return; }
	
	ATacticalGridTile* StartTile = TacticalGrid->GetTile(FIntPoint(0,0));
	ATacticalGridTile* EndTile = TacticalGrid->GetTile(FIntPoint(4,4));
	
	if (!ensure(StartTile) || !ensure(EndTile)) { return; }
	
	TArray<ATacticalGridTile*> Path = TacticalGrid->GetPathfinder()->FindPath(StartTile, EndTile);

	if (Path.Num() > 0)
	{
		for (ATacticalGridTile* Tile : Path)
		{
			UE_LOG(LogTemp, Warning, TEXT("Tile: %s"), *Tile->GetGridCoordinates().ToString());
		}
	}
}

