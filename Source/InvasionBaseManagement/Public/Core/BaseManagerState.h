// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
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

public:
	ABaseManagerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Player who owns this base
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Base Manager")
	TObjectPtr<APlayerState> OwningPlayerState;

	// Which region this base is located in (e.g., "Europe", "US")
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Base Manager")
	FName BaseRegion; 

	// Worker roster for this base
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Base Manager")
	TArray<TObjectPtr<UWorkerData>> WorkerRoster;

	// Base resources
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Base Manager")
	int32 Credits;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Base Manager")
	int32 Supplies;

	// Worker management
	UFUNCTION(BlueprintCallable, Category = "Base Manager")
	void AddWorker(UWorkerData* NewWorker);
	
	// Server-only function to add a worker (with validation)
	UFUNCTION(Server, Reliable, Category = "Base Manager")
	void Server_AddWorker(UWorkerData* NewWorker);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Base Manager")
	const TArray<UWorkerData*>& GetAllWorkers() const;

protected:
	virtual void BeginPlay() override;
private:
	void InitializeBase();
};
