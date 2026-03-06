// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Pathfinder.generated.h"

/**
 * 
 */

class ATacticalGrid;
class ATacticalGridTile;

struct FPathNode
{
	int32 GCost;
	
	int32 HCost;
	
	int32 GetFCost() const { return GCost + HCost;}	
	
	ATacticalGridTile* Tile;
	
	int32 Parent = -1;
};

UCLASS()
class INVASIONTACTICAL_API UPathfinder : public UObject
{
	GENERATED_BODY()
	
public:
	TArray<ATacticalGridTile*> FindPath(ATacticalGridTile* StartTile, const ATacticalGridTile* EndTile) const;
	
	void InitialiseGrid(ATacticalGrid* Grid) { TacticalGrid = Grid;};
	
private:
	UPROPERTY()
	TObjectPtr<ATacticalGrid> TacticalGrid;
};
