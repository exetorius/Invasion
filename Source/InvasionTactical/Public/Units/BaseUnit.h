// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "TacticalTypes.h"
#include "GameFramework/Actor.h"
#include "BaseUnit.generated.h"

class UWidgetComponent;
class UCapsuleComponent;
class UWorkerData;
class ATacticalGridTile;
class ATacticalGrid;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, int32, NewHealth);

UCLASS()
class INVASIONTACTICAL_API ABaseUnit : public AActor
{
	GENERATED_BODY()

public:
	ABaseUnit();
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	void SetCurrentTile(ATacticalGridTile* NewTile);			
	
	void AddHealth(float HealthToAdd);
	void RemoveHealth(float HealthToRemove);
	void Kill();	
	
	virtual void OnTurnStart();	
	
protected:
	virtual void BeginPlay() override;
	// TODO: Remove once billboard rotation is moved into a UBillboardWidgetComponent subclass
	virtual void Tick(float DeltaTime) override;

private:	
	void BroadcastOnHealthChanged(const int32 NewHealth);
	UPROPERTY(VisibleInstanceOnly)
	float Health = 100.f;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWidgetComponent> HealthBarWidgetComponent;
	
	UPROPERTY(VisibleInstanceOnly)
	int32 MovementPointsRemaining = 10;
	UPROPERTY(EditDefaultsOnly)
	int32 MaxMovementPoints = 10;
	
	UPROPERTY(EditDefaultsOnly)
	int32 CombatSkill = 50;
	
	UPROPERTY(EditDefaultsOnly)
	EFaction Faction = EFaction::None;
	
	UPROPERTY(VisibleInstanceOnly)
	ECombatState CombatState = ECombatState::Healthy;
	
	UPROPERTY(VisibleInstanceOnly)
	ATacticalGridTile* CurrentTile;
	
	// Not UPROPERTY - UWorkerData lives in the InvasionBaseManagement module, which is not yet a dependency.
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
	void ConsumeMovementPoints(const int32 Points);
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
