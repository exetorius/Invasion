// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Data/MissionData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MissionBridgeSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class INVASIONCORE_API UMissionBridgeSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void SetPendingSquad(const TArray<FMissionSoldier>& Squad);
	const TArray<FMissionSoldier>& GetPendingSquad() const;
	void ClearPendingSquad();
	
	void SetPendingMissionResult(const FMissionResult& Result);
	const FMissionResult& GetPendingMissionResult() const;
	void ClearPendingMissionResult();
	
private:
	TArray<FMissionSoldier> PendingSquad;
	FMissionResult PendingMissionResult;
};
