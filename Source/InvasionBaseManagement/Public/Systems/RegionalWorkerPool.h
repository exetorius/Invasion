// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Data/WorkerTypes.h"
#include "RegionalWorkerPool.generated.h"

class UWorkerData;

/**
 * Server-owned regional worker pool
 * Generates and manages available workers for hire in a specific region
 * Players can hire workers from this pool into their BaseManagerState
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API ARegionalWorkerPool : public AInfo
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE(FOnAvailableWorkersChanged);
	FOnAvailableWorkersChanged OnAvailableWorkersChanged;
	
	ARegionalWorkerPool();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Server: Generate initial worker pool
	UFUNCTION(BlueprintCallable, Category = "Regional Pool")
	void GenerateInitialWorkerPool(int32 SoldiersCount, int32 ScientistsCount, int32 EngineersCount, int32 MedicsCount, int32 PilotsCount);
	
	// Server: Hire a worker from this pool (removes from pool)
	UFUNCTION(Server, Reliable, Category = "Regional Pool")
	void Server_HireWorker(UWorkerData* Worker, class ABaseManagerState* HiringBase);

	// Server: Return a worker to the pool (fired/dismissed)
	UFUNCTION(Server, Reliable, Category = "Regional Pool")
	void Server_ReturnWorker(UWorkerData* Worker);
	
	void SetRegionID(FName NewRegionID) { RegionID = NewRegionID; }

	
protected:
	virtual void BeginPlay() override;

private:
	// Region identifier (e.g., "Europe", "US", "Asia")
	UPROPERTY(Replicated, EditAnywhere)
	FName RegionID;

	// Workers available for hire in this region
	UPROPERTY(ReplicatedUsing=OnRep_AvailableWorkers)
	TArray<TObjectPtr<UWorkerData>> AvailableWorkers;		

	// Generate a random worker of a specified role
	TObjectPtr<UWorkerData> GenerateRandomWorker(EWorkerRole WorkerRole);

	// Helper: Random name generation
	FString GenerateRandomName();
	
	// Server-only function to add a worker (with validation)
	void AddGeneratedWorker(UWorkerData* NewWorker);
	
	// Client side functionality
	UFUNCTION()
	void OnRep_AvailableWorkers();	
	
// Getters & Setters
public:
	const TArray<UWorkerData*>& GetAvailableWorkers() const { return AvailableWorkers; }
	FName GetRegionID() const { return RegionID; }
	
	// Get all workers of a specific role
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Regional Pool")
	TArray<UWorkerData*> GetWorkersByRole(EWorkerRole WorkerRole) const;
};
