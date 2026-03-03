// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "TacticalTypes.h"
#include "GameFramework/Actor.h"
#include "BaseUnit.generated.h"

class UWorkerData;
class ATacticalGridTile;

UCLASS()
class INVASIONTACTICAL_API ABaseUnit : public AActor
{
	GENERATED_BODY()

public:
	ABaseUnit();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly)
	float Health = 100.f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;
	
	UPROPERTY(VisibleInstanceOnly)
	int32 MovementPointsRemaining = 10;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxMovementPoints = 10;
	
	UPROPERTY(EditDefaultsOnly)
	EFaction Faction;
	
	UPROPERTY(VisibleInstanceOnly)
	ECombatState CombatState = ECombatState::Healthy;
	
	UPROPERTY(VisibleInstanceOnly)
	ATacticalGridTile* CurrentTile;
	
	UPROPERTY()
	UWorkerData* WorkerData = nullptr; // TODO - pass this in dynamically after POC
	
	
};
