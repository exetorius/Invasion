// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "EnemyUnit.generated.h"

class ATacticalGrid;
class ACombatManager;
class ATurnManager;

UCLASS()
class INVASIONTACTICAL_API AEnemyUnit : public ABaseUnit
{
	GENERATED_BODY()

public:
	AEnemyUnit();
	virtual void OnTurnStart() override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxShootRange = 8;
	
	UPROPERTY()
	TObjectPtr<ATurnManager> TurnManager;
	UPROPERTY()
	TObjectPtr<ACombatManager> CombatManager;
	UPROPERTY()
	TObjectPtr<ATacticalGrid> TacticalGrid;

};
