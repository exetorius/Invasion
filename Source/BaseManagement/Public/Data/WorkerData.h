#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Data/WorkerTypes.h"
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

	// Enable replication support for UObject
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Worker")
	FGuid UniqueID;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Worker")
	FString Name;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Worker")
	int32 Age;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Worker")
	ERace Race;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Worker")
	ESpecies Species;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Worker")
	EWorkerRole WorkerRole;
};
