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
	
	UPROPERTY(BlueprintReadOnly)
	FGuid TaskID = FGuid::NewGuid();
	
	UPROPERTY(BlueprintReadOnly)
	FString TaskName;
	
	UPROPERTY(BlueprintReadOnly)
	ETaskType TaskType;
	
	UPROPERTY(BlueprintReadOnly)
	int32 MaxWorkers;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FGuid> AssignedWorkerIDs;
	
	UPROPERTY(BlueprintReadOnly)
	float Progress;
	
	UPROPERTY(BlueprintReadOnly)
	float BaseDuration;
};
