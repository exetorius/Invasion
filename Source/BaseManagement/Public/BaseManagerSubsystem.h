#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WorkerData.h"
#include "BaseManagerSubsystem.generated.h"

UCLASS()
class BASEMANAGEMENT_API UBaseManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "Base Manager")
	void AddWorker(UWorkerData* NewWorker);

	UFUNCTION(BlueprintCallable, Category = "Base Manager")
	UWorkerData* CreateAndAddTestWorker(const FString& Name, int32 Age, const FString& Race, const FString& Species);

	UFUNCTION(BlueprintCallable, Category = "Base Manager")
	const TArray<UWorkerData*>& GetAllWorkers() const;

private:
	UPROPERTY()
	TArray<UWorkerData*> WorkerRoster;
};
