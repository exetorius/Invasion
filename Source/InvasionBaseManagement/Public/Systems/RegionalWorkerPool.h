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
	ARegionalWorkerPool();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Region identifier (e.g., "Europe", "US", "Asia")
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Regional Pool")
	FName RegionID;

	// Workers available for hire in this region
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Regional Pool")
	TArray<TObjectPtr<UWorkerData>> AvailableWorkers;

	// Get all workers of a specific role
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Regional Pool")
	TArray<UWorkerData*> GetWorkersByRole(EWorkerRole WorkerRole) const;

	// Server: Hire a worker from this pool (removes from pool)
	UFUNCTION(Server, Reliable, Category = "Regional Pool")
	void Server_HireWorker(UWorkerData* Worker, class ABaseManagerState* HiringBase);

	// Server: Return a worker to the pool (fired/dismissed)
	UFUNCTION(Server, Reliable, Category = "Regional Pool")
	void Server_ReturnWorker(UWorkerData* Worker);

	// Server: Generate initial worker pool
	UFUNCTION(BlueprintCallable, Category = "Regional Pool")
	void GenerateInitialWorkerPool(int32 SoldiersCount, int32 ScientistsCount, int32 EngineersCount, int32 MedicsCount, int32 PilotsCount);

protected:
	virtual void BeginPlay() override;

private:
	// Generate a random worker of a specified role
	TObjectPtr<UWorkerData> GenerateRandomWorker(EWorkerRole WorkerRole);

	// Helper: Random name generation
	FString GenerateRandomName();
};
