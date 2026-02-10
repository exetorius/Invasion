// CopyrightNotice

#include "Core/BaseManagerState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerState.h"

ABaseManagerState::ABaseManagerState()
{
	// Enable replication
	bReplicates = true;
	bAlwaysRelevant = true; // Always replicate to all clients

	// Initialize resources
	Credits = 1000;
	Supplies = 500;

	// Set tick to false (we don't need per-frame updates)
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseManagerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate all properties to owning client only (for now - can change to all clients later if needed)
	DOREPLIFETIME(ABaseManagerState, OwningPlayerState);
	DOREPLIFETIME(ABaseManagerState, WorkerRoster);
	DOREPLIFETIME(ABaseManagerState, Credits);
	DOREPLIFETIME(ABaseManagerState, Supplies);
}

void ABaseManagerState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		InitializeBase();
	}
}

void ABaseManagerState::InitializeBase()
{
	UE_LOG(LogTemp, Log, TEXT("BaseManagerState initialized for player: %s"),
		OwningPlayerState ? *OwningPlayerState->GetPlayerName() : TEXT("Unknown"));
}

void ABaseManagerState::AddWorker(UWorkerData* NewWorker)
{
	// Client calls server version
	if (!HasAuthority())
	{
		Server_AddWorker(NewWorker);
		return;
	}

	// Server-side execution
	if (NewWorker)
	{
		WorkerRoster.Add(NewWorker);
		UE_LOG(LogTemp, Log, TEXT("Added worker: %s to base owned by %s"),
			*NewWorker->Name,
			OwningPlayerState ? *OwningPlayerState->GetPlayerName() : TEXT("Unknown"));
	}
}

void ABaseManagerState::Server_AddWorker_Implementation(UWorkerData* NewWorker)
{
	if (NewWorker)
	{
		WorkerRoster.Add(NewWorker);
		UE_LOG(LogTemp, Log, TEXT("Server: Added worker: %s"), *NewWorker->Name);
	}
}

const TArray<UWorkerData*>& ABaseManagerState::GetAllWorkers() const
{
	return WorkerRoster;
}

UWorkerData* ABaseManagerState::CreateAndAddWorker(const FString& Name, int32 Age, ERace Race, ESpecies Species, EWorkerRole WorkerRole)
{
	// Only server can create workers
	if (!HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("Client attempted to create worker - must be done on server"));
		return nullptr;
	}

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

		UE_LOG(LogTemp, Log, TEXT("Created Worker: %s (Role: %s)"),
			*Name,
			*UEnum::GetValueAsString(WorkerRole));
	}

	return NewWorker;
}
