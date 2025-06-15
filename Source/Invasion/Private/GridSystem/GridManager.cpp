// CopyrightNotice


#include "GridSystem/GridManager.h"

AGridManager::AGridManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AGridManager::BeginPlay()
{
	Super::BeginPlay();

	// Initialise grid
	for (int32 X =0; X < GridWidth; X++)
	{
		for (int32 Y = 0; Y < GridHeight; Y++)
		{
			FGridCell NewCell;
			NewCell.Location = FVector(X * CellSize, Y * CellSize, 5);
			GridCells.Add(NewCell);

			// Draw Debug Box for each cell
			FVector BoxExtents = FVector(CellSize / 2, CellSize / 2, NewCell.Location.Z + CellSize);
			DrawDebugBox(GetWorld(), NewCell.Location, BoxExtents, FColor::Green, false, 30.f);
		}
	}
}


