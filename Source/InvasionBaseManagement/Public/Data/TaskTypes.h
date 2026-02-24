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

	UPROPERTY(BlueprintReadOnly, Meta = (IgnoreForMemberInitializationTest))
	FGuid TaskID = FGuid::NewGuid();

	UPROPERTY(BlueprintReadOnly)
	FString TaskName;

	UPROPERTY(BlueprintReadOnly)
	ETaskType TaskType = ETaskType::ETT_Research;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxWorkers = 0;

	UPROPERTY(BlueprintReadOnly)
	TArray<FGuid> AssignedWorkerIDs;

	UPROPERTY(BlueprintReadOnly)
	float Progress = 0.f;

	UPROPERTY(BlueprintReadOnly)
	float BaseDuration = 0.f;
};
