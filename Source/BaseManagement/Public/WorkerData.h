#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WorkerTypes.h"
#include "WorkerData.generated.h"

/*
 * Base worker data, for more specific role data use a subclass that inherits from here. Can be used for a generic NPC maybe?
 */

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
	ERace Race;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Worker")
	ESpecies Species;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Worker")
	EWorkerRole WorkerRole;
};
