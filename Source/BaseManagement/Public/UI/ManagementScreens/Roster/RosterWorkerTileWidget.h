// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RosterWorkerTileWidget.generated.h"

/**
 * Widget representing a single worker in the roster list
 * Displays worker name, role, age, race, species
 */
UCLASS()
class BASEMANAGEMENT_API URosterWorkerTileWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Set the worker data and update UI
	UFUNCTION(BlueprintCallable, Category = "Roster")
	void SetWorkerData(class UWorkerData* Worker);

	// Get the current worker data
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Roster")
	UWorkerData* GetWorkerData() const { return WorkerData; }

protected:
	// Called after SetWorkerData to update UI elements
	// Implement this in Blueprint to bind text blocks, images, etc.
	UFUNCTION(BlueprintImplementableEvent, Category = "Roster")
	void OnWorkerDataSet(UWorkerData* Worker);

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Roster")
	TObjectPtr<UWorkerData> WorkerData;
};
