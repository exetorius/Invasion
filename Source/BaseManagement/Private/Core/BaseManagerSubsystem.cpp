#include "Core/BaseManagerSubsystem.h"
#include "Engine/Engine.h"

void UBaseManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogTemp, Log, TEXT("BaseManagerSubsystem Initialized"));
}

void UBaseManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	WorkerRoster.Empty();
}

void UBaseManagerSubsystem::AddWorker(UWorkerData* NewWorker)
{
	if (NewWorker)
	{
		WorkerRoster.Add(NewWorker);
		UE_LOG(LogTemp, Log, TEXT("Added worker: %s"), *NewWorker->Name);
	}
}

const TArray<UWorkerData*>& UBaseManagerSubsystem::GetAllWorkers() const
{
	return WorkerRoster;
}

// TEST FUNCTIONS

UWorkerData* UBaseManagerSubsystem::CreateAndAddTestWorker(const FString& Name, int32 Age,  ERace Race,  ESpecies Species, EWorkerRole WorkerRole)
{
	UWorkerData* NewWorker = NewObject<UWorkerData>(this);
	if (NewWorker)
	{
		NewWorker->UniqueID = FGuid::NewGuid();
		NewWorker->Name = Name;
		NewWorker->Age = Age;
		NewWorker->Race = Race;
		NewWorker->Species = Species;
		NewWorker->WorkerRole = WorkerRole;

		AddWorker(NewWorker);

		UE_LOG(LogTemp, Log, TEXT("Created Worker: %s (Role: %s)"), *Name, *UEnum::GetValueAsString(WorkerRole));
	}

	return NewWorker;
}
