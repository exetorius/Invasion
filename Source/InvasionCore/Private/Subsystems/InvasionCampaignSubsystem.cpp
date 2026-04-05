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

UWorkerData* UInvasionCampaignSubsystem::FindWorkerByID(const FGuid& WorkerID) const
{
	if (!WorkerID.IsValid()) { return nullptr; }

	for (UWorkerData* Worker : Roster)
	{
		if (Worker && Worker->GetWorkerUniqueID() == WorkerID)
		{
			return Worker;
		}
	}
	
	return nullptr;
}

void UInvasionCampaignSubsystem::AddWorker(UWorkerData* NewWorker)
{
	if (!NewWorker) { return; }
	
	Roster.Add(NewWorker);
	OnWorkerAdded.Broadcast(NewWorker);
}

void UInvasionCampaignSubsystem::RemoveWorker(UWorkerData* WorkerToRemove)
{
	if (!WorkerToRemove) { return; }
	
	Roster.Remove(WorkerToRemove);
	OnWorkerRemoved.Broadcast(WorkerToRemove);
}
