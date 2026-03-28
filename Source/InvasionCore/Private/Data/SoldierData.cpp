// CopyrightNotice


#include "Data/SoldierData.h"

#include <Mmdeviceapi.h>

#include "Net/UnrealNetwork.h"

void USoldierData::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USoldierData, KillCount);
	DOREPLIFETIME(USoldierData, UnitRank);
	DOREPLIFETIME(USoldierData, InjurySeverity);
}

TObjectPtr<USoldierData> USoldierData::CreateSoldier(UObject* Outer)
{
	USoldierData* Soldier = NewObject<USoldierData>(Outer);
	if (!Soldier)
	{
		UE_LOG(LogTemp, Warning, TEXT("SoldierData: Failed to create soldier"));
		return nullptr;
	}
	
	Soldier->SetRace(EWorkerRace::Human);
	Soldier->SetRole(EWorkerRole::Soldier);

	return Soldier;
}