#pragma once

#include "CoreMinimal.h"
#include "MissionData.generated.h"

USTRUCT(BlueprintType)
struct INVASIONCORE_API FMissionSoldier
{
	GENERATED_BODY()

	UPROPERTY()
	FGuid WorkerID = FGuid();

	UPROPERTY()
	FText DisplayName = FText::GetEmpty();
};

USTRUCT(BlueprintType)
struct INVASIONCORE_API FMissionResult
{
	GENERATED_BODY()
	
	UPROPERTY()
	bool bVictory = false;
	
	UPROPERTY()
	TArray<FGuid> CasualtyIDs;
	
	UPROPERTY()
	int32 CreditsAwarded = 0;
};