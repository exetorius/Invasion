// CopyrightNotice


#include "Grid/TacticalGrid.h"

#include "Pathfinder.h"
#include "Grid/TacticalGridTile.h"


ATacticalGrid::ATacticalGrid()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATacticalGrid::BeginPlay()
{
	Super::BeginPlay();
	
	if (!ensure(TileClass)) { return; }
	
	for (int32 Y = 0; Y < GridHeight; Y++)
	{
		for (int32 X = 0; X < GridWidth; X++)
		{
			FTransform Transform;
			Transform.SetLocation(GetActorLocation() + FVector(X * TileSize, Y * TileSize, 0.f));			
			
			if (ATacticalGridTile* Tile = GetWorld()->SpawnActor<ATacticalGridTile>(TileClass, Transform))
			{
				Tile->SetGridCoordinates(FIntPoint(X, Y));
				Tiles.Add(Tile);				
				
				if (bDebugDraw)
				{
					FColor DebugColor = Tile->IsWalkable() ? FColor::Green : FColor::Red;
					DrawDebugBox(GetWorld(), Tile->GetActorLocation(), FVector(TileSize/2, TileSize/2, 0.f), DebugColor, true, 0,0, 10);
				}
			}			
		}
	}
	
	Pathfinder = NewObject<UPathfinder>(this);
	Pathfinder->InitialiseGrid(this);
}

int32 ATacticalGrid::CoordinateToIndex(FIntPoint Coordinates) const
{
	if (Coordinates.X < 0 || Coordinates.Y < 0 || Coordinates.X >= GridWidth || Coordinates.Y >= GridHeight)
	{
		return INDEX_NONE;
	}
	return Coordinates.X + Coordinates.Y * GridWidth;
}

ATacticalGridTile* ATacticalGrid::GetTile(FIntPoint Coordinates) const
{
	const int32 Index = CoordinateToIndex(Coordinates);
	return Index != INDEX_NONE ? Tiles[Index] : nullptr;
}

TArray<ATacticalGridTile*> ATacticalGrid::GetNeighbours(FIntPoint Coordinates) const
{
	const FIntPoint CardinalOffsets[] = { FIntPoint(0,1), FIntPoint(1,0), FIntPoint(0,-1), FIntPoint(-1,0) };
	TArray<ATacticalGridTile*> Neighbours;
	for (const FIntPoint& Offset : CardinalOffsets)
	{
		if (ATacticalGridTile* NeighbourTile = GetTile(Coordinates + Offset))
		{
			Neighbours.Add(NeighbourTile);
		}
	}
	return Neighbours;	
}

TArray<ATacticalGridTile*> ATacticalGrid::GetTilesInRange(FIntPoint Origin, int32 Range) const
{
	TArray<ATacticalGridTile*> InRangeTiles;
	
	// Manhattan distance = FMath::Abs(X1 - X2) + FMath::Abs(Y1 - Y2)
	for (ATacticalGridTile* Tile : Tiles)
	{
		const FIntPoint TileCoordinates = Tile->GetGridCoordinates();
		if (TileCoordinates == Origin) { continue; } // Skip the current tile so we dont use movement points, Always in range anyways
		if (FMath::Abs(Origin.X - TileCoordinates.X) + FMath::Abs(Origin.Y - TileCoordinates.Y) <= Range)
		{
			InRangeTiles.Add(Tile);
		}
	}
	return InRangeTiles;
}

FIntPoint ATacticalGrid::GetGridLocationFromWorld(FVector WorldLocation) const
{
	return  FIntPoint((WorldLocation.X - GetActorLocation().X) / TileSize, (WorldLocation.Y - GetActorLocation().Y) / TileSize);
}

FVector ATacticalGrid::GetWorldLocationFromGrid(FIntPoint Coordinates) const
{
	return FVector((Coordinates.X * TileSize) + GetActorLocation().X, (Coordinates.Y * TileSize) + GetActorLocation().Y, GetActorLocation().Z);
}


