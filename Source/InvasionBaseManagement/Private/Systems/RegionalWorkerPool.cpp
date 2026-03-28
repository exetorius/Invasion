// CopyrightNotice

#include "Systems/RegionalWorkerPool.h"
#include "Data/WorkerData.h"
#include "Core/BaseManagerState.h"
#include "Data/SoldierData.h"
#include "Net/UnrealNetwork.h"

ARegionalWorkerPool::ARegionalWorkerPool()
{
	// Enable replication
	bReplicates = true;
	bAlwaysRelevant = true; // All clients should see available workers
	
	// CRITICAL: Required for AddReplicatedSubObject() to work
	bReplicateUsingRegisteredSubObjectList = true;

	// Default region
	RegionID = FName("DefaultRegion");

	// No tick needed
	PrimaryActorTick.bCanEverTick = false;
}

void ARegionalWorkerPool::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARegionalWorkerPool, RegionID);
	DOREPLIFETIME(ARegionalWorkerPool, AvailableWorkers);
}

void ARegionalWorkerPool::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Log, TEXT("RegionalWorkerPool '%s' initialized"), *RegionID.ToString());
	}
}

void ARegionalWorkerPool::OnRep_AvailableWorkers()
{
	UE_LOG(LogTemp, Log, TEXT("RegionalWorkerPool: WorkerRoster replicated! Count: %d"), AvailableWorkers.Num());
	
	OnAvailableWorkersChanged.Broadcast();
}

void ARegionalWorkerPool::Server_HireWorker_Implementation(UWorkerData* Worker, ABaseManagerState* HiringBase)
{
	if (!Worker || !HiringBase)
	{
		UE_LOG(LogTemp, Warning, TEXT("RegionalWorkerPool: Hire failed - invalid worker or base"));
		return;
	}

	// Check if this worker exists in this pool
	if (!AvailableWorkers.Contains(Worker))
	{
		UE_LOG(LogTemp, Warning, TEXT("RegionalWorkerPool: Worker '%s' not found in pool"), *Worker->GetWorkerName());
		return;
	}

	// Remove from available pool
	AvailableWorkers.Remove(Worker);
	
	// CRITICAL: De-register as a replicated subobject to replicate to clients
	RemoveReplicatedSubObject(Worker);

	// Add to hiring base
	HiringBase->AddWorker(Worker);

	UE_LOG(LogTemp, Log, TEXT("RegionalWorkerPool '%s': Hired '%s' (%s)"),
		*RegionID.ToString(),
		*Worker->GetWorkerName(),
		*UEnum::GetValueAsString(Worker->GetRole()));
	
	OnAvailableWorkersChanged.Broadcast();
}

void ARegionalWorkerPool::Server_ReturnWorker_Implementation(UWorkerData* Worker)
{
	if (!Worker)
	{
		UE_LOG(LogTemp, Warning, TEXT("RegionalWorkerPool: Return failed - invalid worker"));
		return;
	}
	
	if (AvailableWorkers.Contains(Worker))
	{
		UE_LOG(LogTemp, Warning, TEXT("RegionalWorkerPool: Return failed - worker already in pool"));
		return;
	}

	AvailableWorkers.Add(Worker);
	
	// CRITICAL: Register as a replicated subobject to replicate to clients
	AddReplicatedSubObject(Worker);
	
	UE_LOG(LogTemp, Log, TEXT("RegionalWorkerPool '%s': Added worker: %s"),
		*RegionID.ToString(),
		*Worker->GetWorkerName());
	
	OnAvailableWorkersChanged.Broadcast();
}

void ARegionalWorkerPool::AddGeneratedWorker(UWorkerData* NewWorker)
{
	if (NewWorker)
	{
		AvailableWorkers.Add(NewWorker);
		
		// CRITICAL: Register as a replicated subobject to replicate to clients
		AddReplicatedSubObject(NewWorker);
		
		UE_LOG(LogTemp, Log, TEXT("RegionalWorkerPool '%s': Added worker: %s"),
			*RegionID.ToString(),
			*NewWorker->GetWorkerName());		
	}
}

void ARegionalWorkerPool::GenerateInitialWorkerPool(int32 SoldiersCount, int32 ScientistsCount, int32 EngineersCount, int32 MedicsCount, int32 PilotsCount)
{
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("RegionalWorkerPool: Only server can generate workers"));
		return;
	}

	// Generate soldiers
	for (int32 i = 0; i < SoldiersCount; ++i)
	{
		if (USoldierData* Soldier = GenerateRandomSoldier())
		{
			AddGeneratedWorker(Soldier);
		}
	}

	// Generate scientists
	for (int32 i = 0; i < ScientistsCount; ++i)
	{
		if (UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::Scientist))
		{
			AddGeneratedWorker(Worker);
		}
	}

	// Generate engineers
	for (int32 i = 0; i < EngineersCount; ++i)
	{
		if (UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::Engineer))
		{
			AddGeneratedWorker(Worker);
		}
	}

	// Generate medics
	for (int32 i = 0; i < MedicsCount; ++i)
	{
		if (UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::Medic))
		{
			AddGeneratedWorker(Worker);
		}
	}

	// Generate pilots
	for (int32 i = 0; i < PilotsCount; ++i)
	{
		if (UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::Pilot))
		{
			AddGeneratedWorker(Worker);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("RegionalWorkerPool '%s': Generated %d workers"),
		*RegionID.ToString(),
		AvailableWorkers.Num());
	
	OnAvailableWorkersChanged.Broadcast();
}

TObjectPtr<UWorkerData> ARegionalWorkerPool::GenerateRandomWorker(EWorkerRole WorkerRole)
{
	// TODO: Update method so race can be random instead of fixed Human
	UWorkerData* NewWorker = UWorkerData::CreateWorker(this, WorkerRole, EWorkerRace::Human);
	if (!NewWorker)
	{
		UE_LOG(LogTemp, Warning, TEXT("RegionalWorkerPool: Failed to generate worker"));
		return nullptr;
	}
	
	// --- IDENTITY ---
	NewWorker->SetWorkerName(GenerateRandomName());
	
	// --- HEALTH STATS ---
	NewWorker->SetMaxHealth(100.0f);
	NewWorker->SetHealth(NewWorker->GetMaxHealth());
	
	// --- STATE ---
	NewWorker->SetCurrentStatus(EWorkerStatus::Idle);
	
	UE_LOG(LogTemp, Log, TEXT("Generated Worker: %s (%s)"),
		*NewWorker->GetWorkerName(),
		*UEnum::GetValueAsString(NewWorker->GetRole())
		);
	
	return NewWorker;
}

TObjectPtr<USoldierData> ARegionalWorkerPool::GenerateRandomSoldier()
{
	USoldierData* NewSoldier = USoldierData::CreateSoldier(this);
	if (!NewSoldier)
	{
		UE_LOG(LogTemp, Warning, TEXT("RegionalWorkerPool: Failed to generate soldier"));
		return nullptr;
	}
	
	NewSoldier->SetWorkerName(GenerateRandomName());
	
	NewSoldier->SetMaxHealth(100.0f);
	NewSoldier->SetHealth(NewSoldier->GetMaxHealth());
	
	NewSoldier->SetCurrentStatus(EWorkerStatus::Idle);
	
	return NewSoldier;
}

// TODO: Come up with a better name generation system 
FString ARegionalWorkerPool::GenerateRandomName()
{
	// Simple name generation - can be expanded later
	static const TArray<FString> FirstNames = {
		TEXT("John"), TEXT("Sarah"), TEXT("Michael"), TEXT("Emma"), TEXT("David"),
		TEXT("Lisa"), TEXT("James"), TEXT("Anna"), TEXT("Robert"), TEXT("Maria"),
		TEXT("Chen"), TEXT("Yuki"), TEXT("Ivan"), TEXT("Pierre"), TEXT("Hans")
	};

	static const TArray<FString> LastNames = {
		TEXT("Smith"), TEXT("Johnson"), TEXT("Williams"), TEXT("Brown"), TEXT("Jones"),
		TEXT("Garcia"), TEXT("Martinez"), TEXT("Davis"), TEXT("Rodriguez"), TEXT("Wilson"),
		TEXT("Chen"), TEXT("Tanaka"), TEXT("Petrov"), TEXT("Dubois"), TEXT("Schmidt")
	};

	const FString FirstName = FirstNames[FMath::RandRange(0, FirstNames.Num() - 1)];
	const FString LastName = LastNames[FMath::RandRange(0, LastNames.Num() - 1)];

	return FString::Printf(TEXT("%s %s"), *FirstName, *LastName);
}

TArray<UWorkerData*> ARegionalWorkerPool::GetWorkersByRole(EWorkerRole WorkerRole) const
{
	TArray<UWorkerData*> FilteredWorkers;

	for (UWorkerData* Worker : AvailableWorkers)
	{
		if (Worker && Worker->GetRole() == WorkerRole)
		{
			FilteredWorkers.Add(Worker);
		}
	}

	return FilteredWorkers;
}
