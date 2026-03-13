// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "TacticalTypes.h"
#include "GameFramework/Actor.h"
#include "TacticalGrid.generated.h"

class ATurnManager;
class ATacticalGridTile;
class UPathfinder;
class ABaseUnit;

UCLASS()
class INVASIONTACTICAL_API ATacticalGrid : public AActor
{
	GENERATED_BODY()

public:
	ATacticalGrid();
	
	UFUNCTION(BlueprintPure)
	ECoverType GetCover(FIntPoint DefenderCoords, FIntPoint AttackerCoords);
	
	void HighlightTilesInRange(ABaseUnit* Unit);
	void ClearHighlights();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	int32 GridLength = 10;
	UPROPERTY(EditAnywhere)
	int32 GridWidth = 10;
	UPROPERTY(EditDefaultsOnly)
	float TileSize = 100.f;
	
	// Set before play starts
	UPROPERTY(EditAnywhere)
	bool bDebugDraw = false;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATacticalGridTile> TileClass;
	UPROPERTY()
	TArray<TObjectPtr<ATacticalGridTile>> Tiles;
	
	int32 CoordinateToIndex(FIntPoint Coordinates) const;
	
	UFUNCTION()
	void OnActiveUnitChanged(ABaseUnit* NewActiveUnit);
	
	UPROPERTY()
	TObjectPtr<UPathfinder> Pathfinder;
	
	UPROPERTY()
	TObjectPtr<ATurnManager> TurnManager;
		
	
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
	UPathfinder* GetPathfinder() const { return Pathfinder; }
};
