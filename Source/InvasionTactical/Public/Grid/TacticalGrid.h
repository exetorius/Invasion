// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TacticalGrid.generated.h"

class ATacticalGridTile;
class UPathfinder;

UCLASS()
class INVASIONTACTICAL_API ATacticalGrid : public AActor
{
	GENERATED_BODY()

public:
	ATacticalGrid();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	int32 GridWidth = 10;
	UPROPERTY(EditDefaultsOnly)
	int32 GridHeight = 10;
	UPROPERTY(EditDefaultsOnly)
	float TileSize = 100.f;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATacticalGridTile> TileClass;
	UPROPERTY()
	TArray<TObjectPtr<ATacticalGridTile>> Tiles;
	
	int32 CoordinateToIndex(FIntPoint Coordinates) const;
	
	//UPROPERTY()
	//TObjectPtr<UPathfinder> Pathfinder;
	
// Getters & setters
public:
	UFUNCTION(BlueprintPure)
	ATacticalGridTile* GetTile(FIntPoint Coordinates) const;
	UFUNCTION(BlueprintPure)
	TArray<ATacticalGridTile*> GetNeighbours(FIntPoint Coordinates) const;
	UFUNCTION(BlueprintPure)
	TArray<ATacticalGridTile*> GetTilesInRange(FIntPoint Origin, int32 Range) const;
	FIntPoint GetGridLocationFromWorld(FVector WorldLocation) const;
	FVector GetWorldLocationFromGrid(FIntPoint Coordinates) const;
	//UPathfinder* GetPathfinder() const { return Pathfinder; } //TODO: Create the class then uncomment
};
