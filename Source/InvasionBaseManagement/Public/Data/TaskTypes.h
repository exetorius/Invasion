#pragma once

#include "CoreMinimal.h"
#include "TaskTypes.generated.h"

UENUM(BlueprintType)
enum class ETaskType : uint8
{
	ETT_Research,
	ETT_Engineering,
	
	ETT_MAX
};

USTRUCT(BlueprintType)
struct FBaseTask
{
	GENERATED_BODY()
	
	UPROPERTY()
	FGuid TaskID = FGuid::NewGuid();
	
	UPROPERTY()
	FString TaskName;
	
	UPROPERTY()
	ETaskType TaskType;
	
	UPROPERTY()
	int32 MaxWorkers;
	
	UPROPERTY()
	TArray<FGuid> AssignedWorkerIDs;
	
	UPROPERTY()
	float Progress;
	
	UPROPERTY()
	float BaseDuration;
};
