// CopyrightNotice


#include "Subsystems/InvasionCampaignSubsystem.h"

#include "Data/WorkerData.h"

void UInvasionCampaignSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UInvasionCampaignSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UInvasionCampaignSubsystem::AddWorker(UWorkerData* NewWorker)
{
	if (!NewWorker) { return; }
	
	Roster.Add(NewWorker);
	OnRosterChanged.Broadcast(NewWorker->GetWorkerUniqueID());
}

void UInvasionCampaignSubsystem::RemoveWorker(UWorkerData* WorkerToRemove)
{
	if (!WorkerToRemove) { return; }
	
	Roster.Remove(WorkerToRemove);
	OnRosterChanged.Broadcast(WorkerToRemove->GetWorkerUniqueID());
}
