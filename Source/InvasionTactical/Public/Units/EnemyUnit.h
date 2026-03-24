// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "EnemyUnit.generated.h"

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
	UPROPERTY()
	TObjectPtr<ATurnManager> TurnManager;
	UPROPERTY()
	TObjectPtr<ACombatManager> CombatManager;
	UPROPERTY()
	TObjectPtr<ATacticalGrid> TacticalGrid;
	
	// TODO: Temp debug — remove DebugEndTurn, DebugEndTurnHandle, and restore AI logic for #33 PIE	re-validation
	FTimerHandle DebugEndTurnHandle;
	void DebugEndTurn() const;

	TArray<ABaseUnit*> FindVisiblePlayers(const TArray<ABaseUnit*>& LivingPlayers, const FIntPoint MyCoords) const;
	ABaseUnit* FindNearestPlayer(const FIntPoint MyCoords, const TArray<ABaseUnit*>& VisiblePlayers) const;
	void MoveAlongPath(const TArray<ATacticalGridTile*>& Path, const FIntPoint& ReferenceCoords);
	void AdvanceToward(const TArray<ABaseUnit*>& LivingPlayers);
	
	// Getters & Setters
public:
	void Initialise(ATurnManager* NewTurnManager, ACombatManager* NewCombatManager, ATacticalGrid* NewTacticalGrid);
};
