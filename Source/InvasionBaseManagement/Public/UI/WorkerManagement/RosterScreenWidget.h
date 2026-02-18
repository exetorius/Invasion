// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "UI/ManagementScreens/BaseManagementScreenWidget.h"
#include "RosterScreenWidget.generated.h"

/**
 * Roster screen - displays list of workers for the player's base
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API URosterScreenWidget : public UBaseManagementScreenWidget
{
	GENERATED_BODY()

public:
	void BindWorkerRosterChangeEvents();
	virtual void NativeConstruct() override;

	// Refresh the worker list from BaseManagerState
	UFUNCTION(BlueprintCallable, Category = "Roster")
	void RefreshWorkerList();

protected:
	void OnWorkerRosterUpdated();
	
	// ScrollBox to hold worker tile widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> WorkerListScrollBox;

	// Class to spawn for each worker tile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Roster")
	TSubclassOf<class URosterWorkerTileWidget> WorkerTileClass;

private:
	void PopulateWorkerList();
	void OnWorkerFired(class UWorkerData* Worker);
};
