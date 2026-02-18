// CopyrightNotice

#include "Systems/RegionalWorkerPool.h"
#include "Data/WorkerData.h"
#include "Core/BaseManagerState.h"
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

	// Check if worker exists in this pool
	if (!AvailableWorkers.Contains(Worker))
	{
		UE_LOG(LogTemp, Warning, TEXT("RegionalWorkerPool: Worker '%s' not found in pool"), *Worker->Name);
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
		*Worker->Name,
		*UEnum::GetValueAsString(Worker->Role));
	
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
		*Worker->Name);
	
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
			*NewWorker->Name);		
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
		UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::EWR_Soldier);
		if (Worker)
		{
			AddGeneratedWorker(Worker);
		}
	}

	// Generate scientists
	for (int32 i = 0; i < ScientistsCount; ++i)
	{
		UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::EWR_Scientist);
		if (Worker)
		{
			AddGeneratedWorker(Worker);
		}
	}

	// Generate engineers
	for (int32 i = 0; i < EngineersCount; ++i)
	{
		UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::EWR_Engineer);
		if (Worker)
		{
			AddGeneratedWorker(Worker);
		}
	}

	// Generate medics
	for (int32 i = 0; i < MedicsCount; ++i)
	{
		UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::EWR_Medic);
		if (Worker)
		{
			AddGeneratedWorker(Worker);
		}
	}

	// Generate pilots
	for (int32 i = 0; i < PilotsCount; ++i)
	{
		UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::EWR_Pilot);
		if (Worker)
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
	UWorkerData* NewWorker = NewObject<UWorkerData>(this);
	if (!NewWorker)
	{
		UE_LOG(LogTemp, Warning, TEXT("RegionalWorkerPool: Failed to generate worker"));
		return nullptr;
	}
	
	// --- IDENTITY ---
	NewWorker->Name = GenerateRandomName();
	NewWorker->Race = EWorkerRace::EWR_Human;
	NewWorker->Role = WorkerRole;
	
	// --- COMBAT STATS ---
	NewWorker->MaxHealth = 100.0f;
	NewWorker->Health = NewWorker->MaxHealth;
	
	// Role-based combat skill ranges
	switch (WorkerRole)
	{
		case EWorkerRole::EWR_Soldier: 
			NewWorker->CombatSkill = FMath::FRandRange(50.0f, 90.0f); 
			break;
		case EWorkerRole::EWR_Medic: 
			NewWorker->CombatSkill = FMath::FRandRange(30.0f, 60.0f); 
			break;
		default: 
			NewWorker->CombatSkill = FMath::FRandRange(10.0f, 50.0f); 
			break; // Scientists/Engineers
	}
	
	// --- WORK STATS ---
	// Role-based work efficiency
	switch (WorkerRole)
	{
	case EWorkerRole::EWR_Scientist:
	case EWorkerRole::EWR_Engineer:
		NewWorker->WorkEfficiency = FMath::FRandRange(60.0f, 95.0f); // Specialists: 60-95
		break;
	default:
		NewWorker->WorkEfficiency = FMath::FRandRange(40.0f, 75.0f); // Others: 40-75
		break;
	}
	
	// --- STATE ---
	NewWorker->Morale = FMath::FRandRange(80.0f, 100.0f);
	NewWorker->InjurySeverity = 0;
	NewWorker->bIsDead = false;
	NewWorker->CurrentStatus = EWorkerStatus::EWS_Idle;
	
	UE_LOG(LogTemp, Log, TEXT("Generated Worker: %s (%s) | Combat: %.1f | Work: %.1f | Morale: %.1f"),
		*NewWorker->Name,
		*UEnum::GetValueAsString(NewWorker->Role),
		NewWorker->CombatSkill,
		NewWorker->WorkEfficiency,
		NewWorker->Morale);
	
	return NewWorker;
}

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
		if (Worker && Worker->Role == WorkerRole)
		{
			FilteredWorkers.Add(Worker);
		}
	}

	return FilteredWorkers;
}
