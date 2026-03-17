#pragma once

#include "CoreMinimal.h"
#include "MissionSoldier.generated.h"

USTRUCT(BlueprintType)
struct INVASIONCORE_API FMissionSoldier
{
	GENERATED_BODY()

	UPROPERTY()
	FGuid WorkerID = FGuid();

	UPROPERTY()
	FText DisplayName = FText::GetEmpty();
};