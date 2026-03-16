// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TacticalGameMode.generated.h"

class ATacticalGrid;
class ATurnManager;
class ACombatManager;
class ABaseUnit;
/**
 * 
 */
UCLASS()
class INVASIONTACTICAL_API ATacticalGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	void RegisterUnit(ABaseUnit* Unit);
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TObjectPtr<ATacticalGrid> TacticalGrid;
	UPROPERTY()
	TObjectPtr<ATurnManager> TurnManager;
	UPROPERTY()
	TObjectPtr<ACombatManager> CombatManager;
	UPROPERTY()
	TArray<TObjectPtr<ABaseUnit>> Units;
	
	int32 ExpectedUnitCount = 0;
};
