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
	// Refresh the worker list from BaseManagerState
	UFUNCTION(BlueprintCallable, Category = "Roster")
	void RefreshWorkerList();

protected:
	virtual void OnScreenDataReady() override;		

private:
	void InitialiseRosterScreen();
	void PopulateWorkerList();
	void BindWorkerRosterChangeEvents();
	
	void OnWorkerRosterUpdated();
	void OnWorkerFired(class UWorkerData* Worker);
	
	// Class to spawn for each worker tile
	UPROPERTY(EditAnywhere, Category = "Roster")
	TSubclassOf<class URosterWorkerTileWidget> WorkerTileClass;
	
	// ScrollBox to hold worker tile widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> WorkerListScrollBox;
};
