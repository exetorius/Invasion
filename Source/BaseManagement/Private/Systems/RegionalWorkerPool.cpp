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

TArray<UWorkerData*> ARegionalWorkerPool::GetWorkersByRole(EWorkerRole WorkerRole) const
{
	TArray<UWorkerData*> FilteredWorkers;

	for (UWorkerData* Worker : AvailableWorkers)
	{
		if (Worker && Worker->WorkerRole == WorkerRole)
		{
			FilteredWorkers.Add(Worker);
		}
	}

	return FilteredWorkers;
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

	// Add to hiring base
	HiringBase->AddWorker(Worker);

	UE_LOG(LogTemp, Log, TEXT("RegionalWorkerPool '%s': Hired '%s' (%s)"),
		*RegionID.ToString(),
		*Worker->Name,
		*UEnum::GetValueAsString(Worker->WorkerRole));
}

void ARegionalWorkerPool::Server_ReturnWorker_Implementation(UWorkerData* Worker)
{
	if (!Worker)
	{
		UE_LOG(LogTemp, Warning, TEXT("RegionalWorkerPool: Return failed - invalid worker"));
		return;
	}

	// Add back to available pool
	AvailableWorkers.Add(Worker);

	UE_LOG(LogTemp, Log, TEXT("RegionalWorkerPool '%s': Worker '%s' returned to pool"),
		*RegionID.ToString(),
		*Worker->Name);
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
			AvailableWorkers.Add(Worker);
		}
	}

	// Generate scientists
	for (int32 i = 0; i < ScientistsCount; ++i)
	{
		UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::EWR_Scientist);
		if (Worker)
		{
			AvailableWorkers.Add(Worker);
		}
	}

	// Generate engineers
	for (int32 i = 0; i < EngineersCount; ++i)
	{
		UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::EWR_Engineer);
		if (Worker)
		{
			AvailableWorkers.Add(Worker);
		}
	}

	// Generate medics
	for (int32 i = 0; i < MedicsCount; ++i)
	{
		UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::EWR_Medic);
		if (Worker)
		{
			AvailableWorkers.Add(Worker);
		}
	}

	// Generate pilots
	for (int32 i = 0; i < PilotsCount; ++i)
	{
		UWorkerData* Worker = GenerateRandomWorker(EWorkerRole::EWR_Pilot);
		if (Worker)
		{
			AvailableWorkers.Add(Worker);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("RegionalWorkerPool '%s': Generated %d workers"),
		*RegionID.ToString(),
		AvailableWorkers.Num());
}

TObjectPtr<UWorkerData> ARegionalWorkerPool::GenerateRandomWorker(EWorkerRole WorkerRole)
{
	UWorkerData* NewWorker = NewObject<UWorkerData>(this);
	if (!NewWorker)
	{
		return nullptr;
	}

	NewWorker->UniqueID = FGuid::NewGuid();
	NewWorker->Name = GenerateRandomName();
	NewWorker->Age = FMath::RandRange(20, 50);
	NewWorker->WorkerRole = WorkerRole;

	// Random race and species
	const int32 RaceRoll = FMath::RandRange(0, 4);
	switch (RaceRoll)
	{
	case 0:
		NewWorker->Race = ERace::ER_Human;
		NewWorker->Species = ESpecies::ES_Terran;
		break;
	case 1:
		NewWorker->Race = ERace::ER_Reptoid;
		NewWorker->Species = ESpecies::ES_Alien;
		break;
	case 2:
		NewWorker->Race = ERace::ER_Sectoid;
		NewWorker->Species = ESpecies::ES_Alien;
		break;
	case 3:
		NewWorker->Race = ERace::ER_Android;
		NewWorker->Species = ESpecies::ES_Robotic;
		break;
	default:
		NewWorker->Race = ERace::ER_Human;
		NewWorker->Species = ESpecies::ES_Terran;
		break;
	}

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
