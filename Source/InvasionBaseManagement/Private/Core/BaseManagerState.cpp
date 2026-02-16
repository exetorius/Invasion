// CopyrightNotice

#include "Core/BaseManagerState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Engine/NetDriver.h"
#include "GameFramework/PlayerState.h"
#include "UObject/UObjectGlobals.h"

ABaseManagerState::ABaseManagerState()
{
	// Enable replication
	bReplicates = true;
	bAlwaysRelevant = true; // Always replicate to all clients

	// CRITICAL: Required for AddReplicatedSubObject() to work
	bReplicateUsingRegisteredSubObjectList = true;

	// Initialize resources
	Credits = 1000;
	Supplies = 500;

	// Set tick to false (we don't need per-frame updates)
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseManagerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate all properties to the owning client only (for now - can change to all clients later if needed)
	DOREPLIFETIME(ABaseManagerState, OwningPlayerState);
	DOREPLIFETIME(ABaseManagerState, BaseRegion);
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
	UE_LOG(LogTemp, Log, TEXT("BaseManagerState initialized for player: %s in region: %s"),
		OwningPlayerState ? *OwningPlayerState->GetPlayerName() : TEXT("Unknown"),
		*BaseRegion.ToString());	
}

void ABaseManagerState::OnRep_WorkerRoster()
{
	UE_LOG(LogTemp, Log, TEXT("BaseManagerState: WorkerRoster replicated! Count: %d"), WorkerRoster.Num());

	// Broadcast to UI that roster changed
	OnWorkerRosterChanged.Broadcast();
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

		// CRITICAL: Register as a replicated subobject to replicate to clients
		AddReplicatedSubObject(NewWorker);

		UE_LOG(LogTemp, Log, TEXT("Added worker: %s to base owned by %s"),
			*NewWorker->Name,
			OwningPlayerState ? *OwningPlayerState->GetPlayerName() : TEXT("Unknown"));

		// Broadcast to UI that roster changed
		OnWorkerRosterChanged.Broadcast();
	}
}

void ABaseManagerState::Server_AddWorker_Implementation(UWorkerData* NewWorker)
{
	if (NewWorker)
	{
		WorkerRoster.Add(NewWorker);

		// CRITICAL: Register as a replicated subobject to replicate to clients
		AddReplicatedSubObject(NewWorker);

		UE_LOG(LogTemp, Log, TEXT("Server: Added worker: %s"), *NewWorker->Name);

		// Broadcast to UI that roster changed
		OnWorkerRosterChanged.Broadcast();
	}
}

const TArray<UWorkerData*>& ABaseManagerState::GetAllWorkers() const
{
	return WorkerRoster;
}
