// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "InvasionCampaignSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorkerAdded, UWorkerData*, Worker);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorkerRemoved, UWorkerData*, Worker);

class UWorkerData;
/**
 * 
 */
UCLASS()
class INVASIONCORE_API UInvasionCampaignSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnWorkerAdded OnWorkerAdded;
	UPROPERTY(BlueprintAssignable)
	FOnWorkerRemoved OnWorkerRemoved;
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
private:
	UPROPERTY()
	TArray<UWorkerData*> Roster;
	
public:
	UFUNCTION(BlueprintCallable)
	const TArray<UWorkerData*>& GetRoster() const { return Roster; }
	UFUNCTION(BlueprintCallable)
	UWorkerData* FindWorkerByID(const FGuid& WorkerID) const;
	UFUNCTION(BlueprintCallable)
	void AddWorker(UWorkerData* NewWorker);
	UFUNCTION(BlueprintCallable)
	void RemoveWorker(UWorkerData* WorkerToRemove);
};
