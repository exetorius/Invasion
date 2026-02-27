// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Data/CampaignTypes.h"
#include "Data/TaskTypes.h"
#include "GameFramework/Info.h"
#include "Data/WorkerData.h"
#include "BaseManagerState.generated.h"

/**
 * Replicated actor that holds per-player base management data
 * Each player has their own BaseManagerState instance
 * This ensures data is synchronized across server and clients in multiplayer
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API ABaseManagerState : public AInfo
{
	GENERATED_BODY()

	//TODO : BIG - Move task management into its own class / subclass? There is going to be a lot of logic perhaps 
	
public:
	DECLARE_MULTICAST_DELEGATE(FOnWorkerRosterChanged);
	FOnWorkerRosterChanged OnWorkerRosterChanged;
	DECLARE_MULTICAST_DELEGATE(FOnTasksChanged);
	FOnTasksChanged OnTasksChanged;
	
	ABaseManagerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;		

	// Worker management
	UFUNCTION(BlueprintCallable, Category = "Base Manager")
	void AddWorker(UWorkerData* NewWorker);
	
	// Server-only function to add a worker (with validation)
	UFUNCTION(Server, Reliable, Category = "Base Manager")
	void Server_AddWorker(UWorkerData* NewWorker);
	
	UFUNCTION(BlueprintCallable, Category = "Base Manager")
	void RemoveWorker(UWorkerData* OldWorker);
	
	// Server-only function to remove a worker (with validation)
	UFUNCTION(Server, Reliable, Category = "Base Manager")
	void Server_RemoveWorker(UWorkerData* OldWorker);	
	
	UFUNCTION(BlueprintCallable, Category = "Base Manager")
	void AssignWorkerToTask(UWorkerData* Worker, FGuid TaskID);
	
	UFUNCTION(BlueprintCallable, Category = "Base Manager")
	void UnassignWorkerFromTask(UWorkerData* Worker, FGuid TaskID);
	
	UWorkerData* FindWorkerByGUID(FGuid WorkerID) const;	

protected:
	virtual void BeginPlay() override;
	
private:
	// Player who owns this base
	UPROPERTY(Replicated)
	TObjectPtr<APlayerState> OwningPlayerState;

	UPROPERTY(Replicated)
	ENation PlayerNation; //   TODO: Player level data - move to PlayerState (check for other player level data properties)
	
	// Which region this base is located in (e.g., "Europe", "US")
	UPROPERTY(Replicated)
	FName BaseRegion; 
	
	// Worker roster for this base
	UPROPERTY(ReplicatedUsing=OnRep_WorkerRoster)
	TArray<TObjectPtr<UWorkerData>> WorkerRoster;
	
	// Task handling
	UPROPERTY(ReplicatedUsing=OnRep_ActiveTasks)
	TArray<FBaseTask> ActiveTasks;	
	
	// Base resources
	UPROPERTY(Replicated)
	int32 Credits;

	UPROPERTY(Replicated)
	int32 Supplies;
	
	void InitializeBase();
	
	// Task timer handling
	FTimerHandle TaskTimerHandle;
	void OnProgressUpdate();
	
	FName DeriveRegionFromNation(ENation Nation) const;
	
	// Client side functionality
	UFUNCTION()
	void OnRep_WorkerRoster();
	UFUNCTION()
	void OnRep_ActiveTasks();	
	
// Getters & Setters
public:	
	APlayerState* GetOwningPlayerState() const { return OwningPlayerState; }
	void SetOwningPlayerState(APlayerState* NewPlayerState) { OwningPlayerState = NewPlayerState; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Manager")
	ENation GetPlayerNation() const { return PlayerNation; }
	void SetPlayerNation(ENation NewNation);
	FName GetBaseRegion() const { return BaseRegion; }
	void SetBaseRegion(FName NewRegion) { BaseRegion = NewRegion; }
	int32 GetCredits() const { return Credits; }
	void AddCredits(int32 CreditsToAdd) { Credits += CreditsToAdd; }
	void RemoveCredits(int32 CreditsToRemove) { Credits = FMath::Max(Credits - CreditsToRemove, 0); }
	int32 GetSupplies() const { return Supplies; }
	void AddSupplies(int32 SuppliesToAdd) { Supplies += SuppliesToAdd; }
	void RemoveSupplies(int32 SuppliesToRemove) { Supplies = FMath::Max(Supplies - SuppliesToRemove, 0); }
	const TArray<FBaseTask>& GetActiveTasks() const { return ActiveTasks; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Manager")
	const TArray<UWorkerData*>& GetAllWorkers() const { return WorkerRoster; }
};
