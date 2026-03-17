// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Data/MissionSoldier.h"
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
	
private:
	TArray<FMissionSoldier> PendingSquad;
};
