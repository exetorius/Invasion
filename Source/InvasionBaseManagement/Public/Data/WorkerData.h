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

	// Enable replication support for UObject
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// --- IDENTITY ---
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category="Identity")
	FGuid UniqueID;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Identity")
	FString Name;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Identity")
	EWorkerRace Race;

	// TODO: Display role as text on the Widget instead of EWR_ROLE 
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Identity")
	EWorkerRole Role;
	
	// -- COMBAT STATS ---
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(ClampMin="0.0"))
	float Health;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(ClampMin="1.0"))
	float MaxHealth;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(ClampMin="0.0", ClampMax="100.0"))
	float CombatSkill;
	
	// --- WORK STATS ---
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Work", meta=(ClampMin="0.0", ClampMax="100.0"))
	float WorkEfficiency;
	
	// --- STATE ---
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="State", meta=(ClampMin="0.0", ClampMax="100.0"))
	float Morale;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="State", meta=(ClampMin="1", ClampMax="3"))
	int32 InjurySeverity;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="State")
	bool bIsDead;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="State")
	EWorkerStatus CurrentStatus;
	
};
