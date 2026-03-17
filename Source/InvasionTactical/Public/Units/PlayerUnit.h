// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "Data/MissionSoldier.h"
#include "PlayerUnit.generated.h"


UCLASS()
class INVASIONTACTICAL_API APlayerUnit : public ABaseUnit
{
	GENERATED_BODY()

public:
	APlayerUnit();
	virtual void OnTurnStart() override;
	
	void MoveToTile(ATacticalGridTile* MoveTile);
	void Initialise(ATacticalGrid* TacticalGrid, const FMissionSoldier& NewSoldierData);

protected:
	virtual void BeginPlay() override;
	
private:
	FMissionSoldier SoldierData;
	
	// Getters & Setters
public:
	UFUNCTION(BlueprintPure)
	FGuid GetSoldierID() const  { return SoldierData.WorkerID; }
	UFUNCTION(BlueprintPure)
	FText GetSoldierName() const { return SoldierData.DisplayName; }
};
