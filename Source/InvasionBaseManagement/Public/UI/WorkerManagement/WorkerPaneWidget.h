// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/ManagementUITypes.h"
#include "WorkerPaneWidget.generated.h"

enum class EWorkerRole : uint8;

/**
 *
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UWorkerPaneWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnAssignClicked OnAssignClicked;
	
	void ShowWorkerList(class ABaseManagerState* BaseManagerState, EWorkerRole WorkerType, FGuid InTaskID);
	void HideWorkerList();

private:
	void InitialiseWorkerPane();
	void OnWorkerSelected(UWorkerData* Worker);
	
	UPROPERTY()
	TObjectPtr<ABaseManagerState> CachedBaseManagerState;
	
	EWorkerRole CachedRoleFilter;	
	FGuid CachedTaskID;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")	
	TSubclassOf<class UWorkerTileBase> WorkerTileWidget;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UScrollBox> WorkerList;
};
