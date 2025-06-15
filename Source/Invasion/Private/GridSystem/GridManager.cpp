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
			FVector BoxLocation = FVector(NewCell.Location.X, NewCell.Location.Y, NewCell.Location.Z + CellSize);
			FVector BoxExtents = FVector(CellSize / 2, CellSize / 2, CellSize);
			DrawDebugBox(GetWorld(), BoxLocation, BoxExtents, FColor::Green, false, 30.f);
		}
	}
}


