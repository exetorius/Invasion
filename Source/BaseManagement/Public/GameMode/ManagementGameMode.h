// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ManagementGameMode.generated.h"

class ARegionalWorkerPool;
class ABaseManagerState;
/**
 * GameMode for base management screen
 * Spawns a BaseManagerState for each player that joins
 */
UCLASS()
class BASEMANAGEMENT_API AManagementGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AManagementGameMode();
	
	virtual void BeginPlay() override;

	// Called when a player logs in - creates their BaseManagerState
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// Get the BaseManagerState for a specific player
	UFUNCTION(BlueprintCallable, Category = "Base Manager")
	ABaseManagerState* GetBaseManagerStateForPlayer(APlayerState* PlayerState) const;
	
	UFUNCTION(BlueprintCallable, Category = "Regional Pools")
	ARegionalWorkerPool* GetRegionalPool(FName RegionID) const;

protected:
	// Class to spawn for each player's base state
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Base Manager")
	TSubclassOf<ABaseManagerState> BaseManagerStateClass;

	// Class for regional worker pools
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Regional Pools")
	TSubclassOf<ARegionalWorkerPool> RegionalWorkerPoolClass;

	// Regions to create on game start
	UPROPERTY(EditDefaultsOnly, Category = "Regional Pools")
	TArray<FName> RegionNames;

	// Default region for new players
	UPROPERTY(EditDefaultsOnly, Category = "Base Manager")
	FName DefaultPlayerRegion;

private:
	// Map of PlayerState to their BaseManagerState
	UPROPERTY()
	TMap<TObjectPtr<APlayerState>, TObjectPtr<ABaseManagerState>> PlayerBaseStates;

	// Map of RegionID to RegionalWorkerPool
	UPROPERTY()
	TMap<FName, TObjectPtr<ARegionalWorkerPool>> RegionalWorkerPools;

	void CreateBaseManagerStateForPlayer(APlayerController* NewPlayer);
	void SpawnRegionalWorkerPools();
};
