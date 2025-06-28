#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WorkerData.generated.h"

UCLASS(Blueprintable)
class BASEMANAGEMENT_API UWorkerData : public UObject
{
	GENERATED_BODY()

public:
	UWorkerData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Worker")
	FGuid UniqueID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Worker")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Worker")
	int32 Age;

	// Maybe swap to ENUM?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Worker")
	FString Race;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Worker")
	FString Species;
	
};
