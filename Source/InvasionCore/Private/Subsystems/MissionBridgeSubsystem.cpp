// CopyrightNotice


#include "Subsystems/MissionBridgeSubsystem.h"

void UMissionBridgeSubsystem::SetPendingSquad(const TArray<FMissionSoldier>& Squad)
{
	PendingSquad = Squad;
}

const TArray<FMissionSoldier>& UMissionBridgeSubsystem::GetPendingSquad() const
{
	return PendingSquad;
}

void UMissionBridgeSubsystem::ClearPendingSquad()
{
	PendingSquad.Empty();
}
