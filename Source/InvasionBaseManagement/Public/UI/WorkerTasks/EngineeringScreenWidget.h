// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "UI/ManagementScreens/BaseManagementScreenWidget.h"
#include "EngineeringScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UEngineeringScreenWidget : public UBaseManagementScreenWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;	
	
protected:
	virtual void OnScreenDataReady() override;
	// ScrollBox to hold task tile widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> TaskListScrollBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UTaskTileWidget> TaskTileWidget;
		
private:
	void InitialiseEngineeringScreen();
	void PopulateTaskList();
	void BindTaskChangeDelegates();
	
	void OnAssignClicked(FGuid TaskID);
	void OnUnassignClicked(FGuid TaskID);
};
