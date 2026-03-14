// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "TacticalTypes.h"
#include "GameFramework/Actor.h"
#include "BaseUnit.generated.h"

class UCapsuleComponent;
class UWorkerData;
class ATacticalGridTile;

UCLASS()
class INVASIONTACTICAL_API ABaseUnit : public AActor
{
	GENERATED_BODY()

public:
	ABaseUnit();
	
	void SetCurrentTile(ATacticalGridTile* NewTile);		
	void Kill();	
	
	void AddHealth(float HealthToAdd);
	void RemoveHealth(float HealthToRemove);
	
	virtual void OnTurnStart();	
	
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
	
	UPROPERTY(EditAnywhere) // TODO: EditAnywhere fine for POC, defaults only later to lock it down
	int32 CombatSkill = 50;
	
	UPROPERTY(EditDefaultsOnly)
	EFaction Faction = EFaction::None;
	
	UPROPERTY(VisibleInstanceOnly)
	ECombatState CombatState = ECombatState::Healthy;
	
	UPROPERTY(VisibleInstanceOnly)
	ATacticalGridTile* CurrentTile;
	
	// Not UPROPERTY - UWorkerData lives in InvasionBaseManagement which is not yet a dependency.
	// Safe for POC as this is always nullptr. Restore UPROPERTY when modules are wired in Phase 3.
	UWorkerData* WorkerData = nullptr; // TODO - pass this in dynamically after POC
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> CapsuleCollider;
	
// Getters & setters
public:
	UFUNCTION(BlueprintPure)
	bool IsAlive() const { return CombatState != ECombatState::Dead; }
	UFUNCTION(BlueprintPure)
	float GetHealth() const { return Health; }
	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const { return MaxHealth; }
	UFUNCTION(BlueprintPure)
	int32 GetMovementPointsRemaining() const { return MovementPointsRemaining; }
	UFUNCTION(BlueprintPure)
	int32 GetMaxMovementPoints() const { return MaxMovementPoints;}
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ConsumeMovementPoints(int32 Points);
	UFUNCTION(BlueprintPure)
	int32 GetCombatSkill() const { return CombatSkill; }
	UFUNCTION(BlueprintPure)
	EFaction GetFaction() const { return Faction; }
	void SetFaction(const EFaction NewFaction);
	UFUNCTION(BlueprintPure)
	ECombatState GetCombatState() const { return CombatState; }
	UFUNCTION(BlueprintPure)
	ATacticalGridTile* GetCurrentTile() const { return CurrentTile; }	
};
