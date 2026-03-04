// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "TacticalTypes.h"
#include "GameFramework/Actor.h"
#include "TacticalGridTile.generated.h"

class ABaseUnit;

UCLASS()
class INVASIONTACTICAL_API ATacticalGridTile : public AActor
{
	GENERATED_BODY()

public:
	ATacticalGridTile();

protected:
	virtual void BeginPlay() override;		
	
private:
	UPROPERTY(EditDefaultsOnly)
	float BoxHalfExtents = 50.0f;
	UPROPERTY(VisibleInstanceOnly)
	FIntPoint TileCoordinates;
	UPROPERTY(VisibleInstanceOnly)
	bool bIsWalkable = true; // Set once at BeginPlay via overlap. TODO: expose setter if dynamic blocking gets introduced (e.g Debris)
	UPROPERTY(EditAnywhere)
	FCoverData CoverData;
	UPROPERTY()
	ABaseUnit* OccupyingUnit;
	
// Getters & Setters
public:
	UFUNCTION(BlueprintPure)
	FIntPoint GetGridCoordinates() const { return TileCoordinates; }
	void SetGridCoordinates(FIntPoint NewCoordinates) { TileCoordinates = NewCoordinates; }	
	UFUNCTION(BlueprintPure)
	bool IsWalkable() const { return bIsWalkable; }
	UFUNCTION(BlueprintPure)
	FCoverData GetCoverData() const { return CoverData; }
	UFUNCTION(BlueprintPure)
	bool IsOccupied() const { return OccupyingUnit != nullptr; }
	UFUNCTION(BlueprintPure)
	ABaseUnit* GetOccupyingUnit() const { return OccupyingUnit; };
	void SetOccupyingUnit(ABaseUnit* NewUnit) { OccupyingUnit = NewUnit; };
};

