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
	DOREPLIFETIME(ABaseManagerState, Credits);
	DOREPLIFETIME(ABaseManagerState, Supplies);
	
	//OnRep functions
	DOREPLIFETIME(ABaseManagerState, WorkerRoster);
	DOREPLIFETIME(ABaseManagerState, ActiveTasks);
}

void ABaseManagerState::OnRep_WorkerRoster()
{
	UE_LOG(LogTemp, Log, TEXT("BaseManagerState: WorkerRoster replicated! Count: %d"), WorkerRoster.Num());

	// Broadcast to UI that roster changed
	OnWorkerRosterChanged.Broadcast();
}

void ABaseManagerState::OnRep_ActiveTasks()
{
	UE_LOG(LogTemp, Log, TEXT("BaseManagerState: ActiveTasks replicated! Count: %d"), ActiveTasks.Num());
	
	OnTasksChanged.Broadcast();
}

void ABaseManagerState::OnProgressUpdate()
{
	if (!HasAuthority()) { return; }
	for (FBaseTask& Task : ActiveTasks)
	{
		if (Task.AssignedWorkerIDs.Num() == 0) { continue; }
		
		FBaseTask ModifiedTask = Task;		
		ModifiedTask.Progress += 1.f * Task.AssignedWorkerIDs.Num();
		if (ModifiedTask.Progress >= ModifiedTask.BaseDuration)
		{
			ModifiedTask.Progress = 0;				
			UE_LOG(LogTemp, Log, TEXT("BaseManagerState: Task %s completed!"), *Task.TaskID.ToString());
		}
		Task = ModifiedTask;		
	}	
	OnTasksChanged.Broadcast();	
}

void ABaseManagerState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		InitializeBase();
		// TODO: Per task timer functiionality tweaks / polish
		GetWorld()->GetTimerManager().SetTimer(TaskTimerHandle, this, &ABaseManagerState::OnProgressUpdate, 1.f, true);
	}
}

void ABaseManagerState::InitializeBase()
{
	UE_LOG(LogTemp, Log, TEXT("BaseManagerState initialized for player: %s in region: %s"),
		OwningPlayerState ? *OwningPlayerState->GetPlayerName() : TEXT("Unknown"),
		*BaseRegion.ToString());	
	
	FBaseTask AlienAlloyTask;
	AlienAlloyTask.TaskName = TEXT("Alien Alloy Analysis");
	AlienAlloyTask.TaskType = ETaskType::ETT_Research;
	AlienAlloyTask.MaxWorkers = 3;
	AlienAlloyTask.BaseDuration = 30;	
	ActiveTasks.Add(AlienAlloyTask);
	
	FBaseTask PlasmaWeaponryTask;
	PlasmaWeaponryTask.TaskName = TEXT("Plasma Weaponry Theory");
	PlasmaWeaponryTask.TaskType = ETaskType::ETT_Research;
	PlasmaWeaponryTask.MaxWorkers = 2;
	PlasmaWeaponryTask.BaseDuration = 60;	
	ActiveTasks.Add(PlasmaWeaponryTask);
	
	FBaseTask NeuralInterfaceTask;
	NeuralInterfaceTask.TaskName = TEXT("Neural Interface Study");
	NeuralInterfaceTask.TaskType = ETaskType::ETT_Research;
	NeuralInterfaceTask.MaxWorkers = 2;
	NeuralInterfaceTask.BaseDuration = 45;	
	ActiveTasks.Add(NeuralInterfaceTask);
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

void ABaseManagerState::RemoveWorker(UWorkerData* OldWorker)
{	
	// Client calls server version
	if (!HasAuthority())
	{
		Server_RemoveWorker(OldWorker);
		return;
	}
	
	// Check if worker exists in this pool
	if (!OldWorker || !WorkerRoster.Contains(OldWorker))
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseManagerState: RemoveWorker called with invalid or unknown worker"));
		return;
	}

	// Server-side execution
	WorkerRoster.Remove(OldWorker);

	// CRITICAL: Remove as a replicated subobject to reduce overheads
	RemoveReplicatedSubObject(OldWorker);

	UE_LOG(LogTemp, Log, TEXT("Removed worker: %s back to pool"),
		*OldWorker->Name);

	// Broadcast to UI that roster changed
	OnWorkerRosterChanged.Broadcast();
}

void ABaseManagerState::Server_RemoveWorker_Implementation(UWorkerData* OldWorker)
{
	// Check if this worker exists in this pool
	if (!OldWorker || !WorkerRoster.Contains(OldWorker))
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseManagerState: RemoveWorker called with invalid or unknown worker"));
		return;
	}

	WorkerRoster.Remove(OldWorker);

	// CRITICAL: Remove as a replicated subobject to reduce overheads
	RemoveReplicatedSubObject(OldWorker);

	UE_LOG(LogTemp, Log, TEXT("Server: Removed worker: %s"), *OldWorker->Name);

	// Broadcast to UI that the roster changed
	OnWorkerRosterChanged.Broadcast();
}

const TArray<UWorkerData*>& ABaseManagerState::GetAllWorkers() const
{
	return WorkerRoster;
}

void ABaseManagerState::AssignWorkerToTask(UWorkerData* Worker, FGuid TaskID)
{
	if (!HasAuthority()) { return; }
	if (!Worker || !TaskID.IsValid() || !WorkerRoster.Contains(Worker)) { return; }
	
	for (FBaseTask& Task : ActiveTasks)
	{
		if (Task.TaskID == TaskID)
		{
			// If a task is already at MaxWorkers, we cannot add anymore workers
			if (Task.AssignedWorkerIDs.Num() >= Task.MaxWorkers)
			{
				UE_LOG(LogTemp, Warning, TEXT("BaseManagerState: Task %s is full!"), *TaskID.ToString());
				return;
			}
			
			// Check the worker isn't already assigned, can't assign the same worker twice
			for (FGuid AssignedWorkerID : Task.AssignedWorkerIDs)
			{				
				if (Worker && Worker->UniqueID == AssignedWorkerID)
				{
					UE_LOG(LogTemp, Log, TEXT("BaseManagerState: Worker %s already assigned to task %s"), *Worker->Name, *TaskID.ToString());
					return;
				}
			}
			
			// Copy - modify - assign to mark struct dirty for replication
			FBaseTask ModifiedTask = Task;
			ModifiedTask.AssignedWorkerIDs.Add(Worker->UniqueID);
			Task = ModifiedTask;
			
			// Assign worker status
			// TODO: Add a field to worker to display what task they are doing
			Worker->CurrentStatus = EWorkerStatus::EWS_Working;
			
			UE_LOG(LogTemp, Log, TEXT("BaseManagerState: Assigned worker %s to task %s"), *Worker->Name, *TaskID.ToString());
			
			OnTasksChanged.Broadcast();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("BaseManagerState: UnassignWorkerFromTask - TaskID not found in ActiveTasks"))
}

void ABaseManagerState::UnassignWorkerFromTask(UWorkerData* Worker, FGuid TaskID)
{
	if (!HasAuthority()) { return; }
	if (!Worker || !TaskID.IsValid() || !WorkerRoster.Contains(Worker)) { return; }
	
	for (FBaseTask& Task : ActiveTasks)
	{
		// We found the task
		if (Task.TaskID == TaskID)
		{
			// We found the user assigned to the task
			if (Task.AssignedWorkerIDs.Contains(Worker->UniqueID))
			{
				FBaseTask ModifiedTask = Task;
				ModifiedTask.AssignedWorkerIDs.Remove(Worker->UniqueID);
				Task = ModifiedTask;
			
				Worker->CurrentStatus = EWorkerStatus::EWS_Idle;
				UE_LOG(LogTemp, Log, TEXT("BaseManagerState: Unassigned worker %s from task %s"), *Worker->Name, *TaskID.ToString());
				OnTasksChanged.Broadcast();
			
				return;
			}
			UE_LOG(LogTemp, Warning, TEXT("BaseManagerState: Worker %s not assigned to task %s"), *Worker->Name, *TaskID.ToString());
		}			
	}
	UE_LOG(LogTemp, Warning, TEXT("BaseManagerState: UnassignWorkerFromTask - TaskID not found in ActiveTasks"));
}

UWorkerData* ABaseManagerState::FindWorkerByGUID(FGuid WorkerID) const
{
	if (!WorkerID.IsValid()) { return nullptr; }
	
	for (UWorkerData* Worker : WorkerRoster)
	{
		if (Worker && Worker->UniqueID == WorkerID)
		{
			UE_LOG(LogTemp, Log, TEXT("BaseManagerState: Found worker with GUID: %s"), *WorkerID.ToString());
			return Worker;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Worker not found in roster for GUID: %s"), *WorkerID.ToString());
	return nullptr;	
}
