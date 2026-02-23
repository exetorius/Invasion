#include "Data/WorkerData.h"
#include "Net/UnrealNetwork.h"

UWorkerData::UWorkerData()
{
	UniqueID = FGuid::NewGuid();
}

TObjectPtr<UWorkerData> UWorkerData::CreateWorker(UObject* Outer, EWorkerRole InRole, EWorkerRace InRace)
{
	UWorkerData* Worker = NewObject<UWorkerData>(Outer);
	if (!Worker)
	{
		UE_LOG(LogTemp, Warning, TEXT("WorkerData: Failed to generate worker"));
		return nullptr;
	}
	
	Worker->Role = InRole;
	Worker->Race = InRace;
	return Worker;
}

void UWorkerData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Identity
	DOREPLIFETIME(UWorkerData, UniqueID);
	DOREPLIFETIME(UWorkerData, Name);
	DOREPLIFETIME(UWorkerData, Race);
	DOREPLIFETIME(UWorkerData, Role);
	
	//Combat Stats
	DOREPLIFETIME(UWorkerData, Health);
	DOREPLIFETIME(UWorkerData, MaxHealth);
	DOREPLIFETIME(UWorkerData, CombatSkill);
	
	// Work Stats
	DOREPLIFETIME(UWorkerData, WorkEfficiency);
	
	// State
	DOREPLIFETIME(UWorkerData, Morale);
	DOREPLIFETIME(UWorkerData, InjurySeverity);
	DOREPLIFETIME(UWorkerData, bIsDead);
	DOREPLIFETIME(UWorkerData, CurrentStatus);
}

