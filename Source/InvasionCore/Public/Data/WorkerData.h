#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Data/WorkerTypes.h"
#include "WorkerData.generated.h"

/*
 * Base worker data, for more specific role data use a subclass that inherits from here. Can be used for a generic NPC maybe?
 */

UCLASS(Blueprintable)
class INVASIONCORE_API UWorkerData : public UObject
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
	void SetRace(const EWorkerRace NewRace) { if (Race == EWorkerRace::Unknown) Race = NewRace; }
	
	// --- ROLE ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	EWorkerRole GetRole() const { return Role; }
	void SetRole(const EWorkerRole NewRole) { if (Role == EWorkerRole::None) Role = NewRole; }
	
	// --- HEALTH ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	float GetHealth() const { return Health; }
	void AddHealth(float HealthToAdd);
	void RemoveHealth(float HealthToRemove);
	void SetHealth(float NewHealth);

	// --- MAX HEALTH ---
	UFUNCTION(BlueprintPure, Category = "Worker")
	float GetMaxHealth() const { return MaxHealth; }
	void AddMaxHealth(float MaxHealthToAdd);
	void RemoveMaxHealth(float MaxHealthToRemove); // TODO: System to reduce based on current MaxHealth
	void SetMaxHealth(float NewMaxHealth); // TODO: Make dynamic based from buffs etc so it can go higher
	
	void Kill() { bIsDead = true; }
	UFUNCTION(BlueprintPure, Category = "Worker")
	bool IsDead() const { return bIsDead; }
	
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
	bool bIsDead = false;
	
	// TODO: Add a field to display worker's current task, activity or status
	UPROPERTY(Replicated)
	EWorkerStatus CurrentStatus;
	
};
