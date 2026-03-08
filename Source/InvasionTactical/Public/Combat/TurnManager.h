// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TacticalTypes.h"
#include "TurnManager.generated.h"

class ABaseUnit;

UCLASS()
class INVASIONTACTICAL_API ATurnManager : public AActor
{
	GENERATED_BODY()
		
public:		
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCombatEnded, bool); // bPlayerWon
	FOnCombatEnded OnCombatEnded;
	
	ATurnManager();
	
	void RegisterUnit(ABaseUnit* Unit);
	void StartCombat();	
	void RequestEndTurn();	
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleInstanceOnly)
	int32 CurrentUnitIndex = 0;
	UPROPERTY(VisibleInstanceOnly)
	int32 CurrentRound = 0;
	
	UPROPERTY(VisibleInstanceOnly)
	ETacticalPhase TurnPhase = ETacticalPhase::None;	
	UPROPERTY(VisibleInstanceOnly)
	ETacticalPhase StartingPhase = ETacticalPhase::None;
	
	UPROPERTY(VisibleInstanceOnly)
	TArray<ABaseUnit*> PlayerUnits;
	UPROPERTY(VisibleInstanceOnly)
	TArray<ABaseUnit*> EnemyUnits;	
	
	bool ShouldStartNextPhase();
	bool HasCombatEnded() const;
	void AdvanceToNextLiveUnit();
	
	const TArray<ABaseUnit*>& GetCurrentTeam() const;
	const TArray<ABaseUnit*>& GetOtherTeam() const;
};
