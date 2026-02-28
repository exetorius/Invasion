// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/TaskTypes.h"
#include "TaskTileWidget.generated.h"

/**
 * Widget representation for a task tile in the worker tasks UI.
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UTaskTileWidget : public UUserWidget
{
	GENERATED_BODY()
	
	// TODO: Subclass this out for engineering / research projects if they become more bespoke?
	
	// TODO: List available workers when selecting a task so you can cheery pick who does what job
	
public:
	DECLARE_DELEGATE_OneParam(FOnAssignClicked, FGuid);
	FOnAssignClicked OnAssignClicked;
	DECLARE_DELEGATE_OneParam(FOnUnassignClicked, FGuid);
	FOnUnassignClicked OnUnassignClicked;
	
	UFUNCTION(BlueprintCallable, Category = "Tasks")
	void OnAssignButtonClicked();
	
	UFUNCTION(BlueprintCallable, Category = "Tasks")
	void OnUnassignButtonClicked();
	
	UFUNCTION(BlueprintCallable, Category = "Tasks")
	void SetTaskData(const FBaseTask& NewTaskData);	
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Tasks")
	void OnTaskDataSet(const FBaseTask& NewTaskData);
	
private:
	FBaseTask TaskData;
};
