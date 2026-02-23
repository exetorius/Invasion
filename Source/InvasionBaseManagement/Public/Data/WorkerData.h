#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Data/WorkerTypes.h"
#include "WorkerData.generated.h"

/*
 * Base worker data, for more specific role data use a subclass that inherits from here. Can be used for a generic NPC maybe?
 */

UCLASS(Blueprintable)
class INVASIONBASEMANAGEMENT_API UWorkerData : public UObject
{
	GENERATED_BODY()

public:
	UWorkerData();
	static TObjectPtr<UWorkerData> CreateWorker(UObject* Outer, EWorkerRole InRole, EWorkerRace InRace);

	// Enable replication support for UObject
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Getters & Setters
	UFUNCTION(BlueprintPure, Category = "Worker")
	FGuid GetWorkerUniqueID() const { return UniqueID; }
	
	// --- NAME ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	FString GetWorkerName() const { return Name; }
	UFUNCTION(BlueprintCallable, Category = "Worker")
	void SetWorkerName(FString NewName) { Name = NewName; }
	
	// --- RACE ---
	UFUNCTION(BlueprintPure, Category = "Worker")		
	EWorkerRace GetRace() const { return Race; }
	
	// --- ROLE ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	EWorkerRole GetRole() const { return Role; }
	
	// --- HEALTH ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	float GetHealth() const { return Health; }
	void AddHealth(float HealthToAdd) { Health = FMath::Min(Health + HealthToAdd, MaxHealth); }
	void RemoveHealth(float HealthToRemove) { Health = FMath::Max(Health - HealthToRemove, 0.f); }
	void SetHealth(float NewHealth) { Health = FMath::Clamp(NewHealth, 0.f, MaxHealth); }

	// --- MAX HEALTH ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	float GetMaxHealth() const { return MaxHealth; }
	void AddMaxHealth(float MaxHealthToAdd) { MaxHealth += MaxHealthToAdd; }
	void RemoveMaxHealth(float MaxHealthToRemove) { MaxHealth = FMath::Max(MaxHealth - MaxHealthToRemove, 0); } // TODO: System to reduce based on current MaxHealth
	void SetMaxHealth(float NewMaxHealth) { MaxHealth = FMath::Clamp(NewMaxHealth, 0, 100); } // TODO: Make dynamic based from buffs etc so it can go higher
	
	void Kill() { bIsDead = true; }
	UFUNCTION(BlueprintPure, Category = "Worker")
	bool IsDead() const { return bIsDead; }
	
	// --- COMBAT SKILL ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	float GetCombatSkill() const { return CombatSkill; }
	void SetCombatSkill(float NewCombatSkill) { CombatSkill = FMath::Clamp(NewCombatSkill, 0.f, 100.f); }
	
	// --- WORK EFFICIENCY ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	float GetWorkEfficiency() const { return WorkEfficiency; }
	void SetWorkEfficiency(float NewWorkEfficiency) { WorkEfficiency = FMath::Clamp(NewWorkEfficiency, 0.f, 100.f); }
	
	// --- MORALE ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	float GetMorale() const { return Morale; }
	void AddMorale(float MoraleToAdd) { Morale = FMath::Clamp(Morale + MoraleToAdd, 0.f, 100.f); } // TODO: Increase max for inspired effect?
	void RemoveMorale(float MoraleToRemove) { Morale = FMath::Clamp(Morale - MoraleToRemove, 0.f, 100.f); } // TODO: Lower than 0 for psychosis? 
	void SetMorale(float NewMorale) { Morale = FMath::Clamp(NewMorale, 0.f, 100.f); }
	
	// --- INJURY SEVERITY ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	EWorkerInjurySeverity GetInjurySeverity() const { return InjurySeverity; }
	void SetInjurySeverity(EWorkerInjurySeverity NewInjurySeverity) { InjurySeverity = NewInjurySeverity; }
	
	// --- STATUS ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	EWorkerStatus GetCurrentStatus() const { return CurrentStatus; }	
	void SetCurrentStatus(EWorkerStatus NewStatus) { CurrentStatus = NewStatus; }
	
private:
	// --- IDENTITY ---
	UPROPERTY(Replicated)
	FGuid UniqueID;

	UPROPERTY(Replicated)
	FString Name;

	UPROPERTY(Replicated)
	EWorkerRace Race;

	// TODO: Display role as text on the Widget instead of EWR_ROLE 
	UPROPERTY(Replicated)
	EWorkerRole Role;
	
	// -- COMBAT STATS ---
	UPROPERTY(Replicated)
	float Health;
	
	UPROPERTY(Replicated)
	float MaxHealth;
	
	UPROPERTY(Replicated)
	float CombatSkill;
	
	// --- WORK STATS ---
	UPROPERTY(Replicated)
	float WorkEfficiency;
	
	// --- STATE ---
	UPROPERTY(Replicated)
	float Morale;
	
	UPROPERTY(Replicated)
	EWorkerInjurySeverity InjurySeverity;
	
	UPROPERTY(Replicated)
	bool bIsDead = false;
	
	// TODO: Add a field to display worker's current task, activity or status
	UPROPERTY(Replicated)
	EWorkerStatus CurrentStatus;
	
};
