#include "Data/WorkerData.h"
#include "Net/UnrealNetwork.h"

UWorkerData::UWorkerData()
{
	UniqueID = FGuid::NewGuid();
}

void UWorkerData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWorkerData, UniqueID);
	DOREPLIFETIME(UWorkerData, Name);
	DOREPLIFETIME(UWorkerData, Age);
	DOREPLIFETIME(UWorkerData, Race);
	DOREPLIFETIME(UWorkerData, Species);
	DOREPLIFETIME(UWorkerData, WorkerRole);
}

