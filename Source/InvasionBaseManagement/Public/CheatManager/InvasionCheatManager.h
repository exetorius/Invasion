// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "InvasionCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UInvasionCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	// --- WORKER TESTING --- \\
	
	// Generate workers in the regional pool for hiring
	// Usage: GenerateWorkerPool 10 5 5 3 2
	UFUNCTION(Exec, Category = "Invasion|Workers")
	void GenerateWorkerPool(int32 Soldiers = 10, int32 Scientists = 5, int32 Engineers = 5, int32 Medics = 3, int32 Pilots = 2);
	
	// Hire N random workers from the pool into player's roster
	// Usage: HireWorkersFromPool 5
	UFUNCTION(Exec, Category = "Invasion|Workers")
	void HireWorkersFromPool(int32 Count = 5);
	
	// --- RESOURCE TESTING --- 
	
	// Add credits to player's base
	// Usage: AddCredits 1000
	UFUNCTION(Exec, Category = "Invasion|Resources")
	void AddCredits(int32 Amount = 1000);
	
	// Add supplies to player's base
	// Usage: AddSupplies 500
	UFUNCTION(Exec, Category = "Invasion|Resources")
	void AddSupplies(int32 Amount = 500);
	
private:
	// Helper: Get the player's BaseManagerState
	class ABaseManagerState* GetPlayerBaseState() const;
	
	// Helper: Get the regional worker pool (finds first one for now)
	class ARegionalWorkerPool* GetRegionalPool() const;
};
