// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "UI/ManagementScreens/BaseManagementScreenWidget.h"
#include "ResearchScreenWidget.generated.h"

/**
 * Displays the list of available tasks provided by the Base Management System
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UResearchScreenWidget : public UBaseManagementScreenWidget
{
	GENERATED_BODY()

protected:
	virtual void OnScreenDataReady() override;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UTaskTileWidget> TaskTileWidget;
		
private:
	void InitialiseResearchScreen();
	void PopulateTaskList();
	void BindTaskChangeDelegates();
	
	// ScrollBox to hold task tile widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> TaskListScrollBox;
	
	void OnAssignClicked(FGuid TaskID);
	void OnUnassignClicked(FGuid TaskID);
	void OnWorkerAssigned(UWorkerData* Worker, FGuid TaskID);
};
