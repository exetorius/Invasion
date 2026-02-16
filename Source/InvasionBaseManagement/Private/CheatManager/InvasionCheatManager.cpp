// CopyrightNotice


#include "CheatManager/InvasionCheatManager.h"

#include "EngineUtils.h"
#include "Controller/ManagementPlayerController.h"
#include "Core/BaseManagerState.h"
#include "Systems/RegionalWorkerPool.h"

void UInvasionCheatManager::GenerateWorkerPool(int32 Soldiers, int32 Scientists, int32 Engineers,
	int32 Medics, int32 Pilots)
{
	ARegionalWorkerPool* Pool = GetRegionalPool();
	if (!Pool)
	{
		UE_LOG(LogTemp, Warning, TEXT("GenerateWorkerPool: No RegionalWorkerPool found in level"));
		return;
	}
	Pool->GenerateInitialWorkerPool(Soldiers, Scientists, Engineers, Medics, Pilots);
	UE_LOG(LogTemp, Warning, TEXT("Generated worker pool with %d total workers"), Soldiers + Scientists + Engineers + Medics + Pilots);
}

void UInvasionCheatManager::HireWorkersFromPool(int32 Count)
{
	ABaseManagerState* BaseState = GetPlayerBaseState();
	ARegionalWorkerPool* Pool = GetRegionalPool();
	
	if (!BaseState)
	{
		UE_LOG(LogTemp, Warning, TEXT("HireWorkersFromPool: No BaseManagerState found for player"));
		return;
	}
	if (!Pool)
	{
		UE_LOG(LogTemp, Warning, TEXT("HireWorkersFromPool: No RegionalWorkerPool found in level"));
		return;
	}
	if (Pool->AvailableWorkers.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("HireWorkersFromPool: Pool is empty! Generate workers first with GenerateWorkerPool"));
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("=== Hiring %d Workers from Pool ==="), Count);
	
	int32 HiredCount = 0;
	for (int32 i = 0; i < Count && Pool->AvailableWorkers.Num() > 0; i++)
	{
		UWorkerData* Worker = Pool->AvailableWorkers[FMath::RandRange(0, Pool->AvailableWorkers.Num() - 1)];
		
		Pool->Server_HireWorker(Worker, BaseState);
		HiredCount++;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("=== Hired %d Workers | Roster: %d | Pool Remaining: %d ==="), 
		HiredCount, 
		BaseState->GetAllWorkers().Num(),
		Pool->AvailableWorkers.Num());
}

void UInvasionCheatManager::AddCredits(int32 Amount)
{
	ABaseManagerState* BaseState = GetPlayerBaseState();
	if (!BaseState)
	{
		UE_LOG(LogTemp, Warning, TEXT("AddCredits: No BaseManagerState found for player"));
		return;
	}
	BaseState->Credits += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Added %d credits. Total: %d"), Amount, BaseState->Credits);
}

void UInvasionCheatManager::AddSupplies(int32 Amount)
{
	ABaseManagerState* BaseState = GetPlayerBaseState();
	if (!BaseState)
	{
		UE_LOG(LogTemp, Warning, TEXT("AddSupplies: No BaseManagerState found for player"));
		return;
	}
	BaseState->Supplies += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Added %d supplies. Total: %d"), Amount, BaseState->Supplies);
}

ABaseManagerState* UInvasionCheatManager::GetPlayerBaseState() const
{
	if (APlayerController* PC = GetOuterAPlayerController())
	{
		if (const AManagementPlayerController* MPC = Cast<AManagementPlayerController>(PC))
		{
			return MPC->GetBaseManagerState();
		}
		UE_LOG(LogTemp, Warning, TEXT("CheatManager: PlayerController is not a ManagementPlayerController!"));		
	}
	return nullptr;
}

ARegionalWorkerPool* UInvasionCheatManager::GetRegionalPool() const
{
	// Find the first regional pool in the world (you could expand this to find by region)
	for (TActorIterator<ARegionalWorkerPool> It(GetWorld()); It; ++It)
	{
		return *It;
	}
	return nullptr;
}
