// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "UI/ManagementScreens/BaseManagementScreenWidget.h"
#include "HiringScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UHiringScreenWidget : public UBaseManagementScreenWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	// Refresh the worker list from BaseManagerState
	UFUNCTION(BlueprintCallable, Category = "Roster")
	void RefreshWorkerList();
	
protected:
	// ScrollBox to hold worker tile widgets
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> WorkerListScrollBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UHiringWorkerTileWidget> WorkerTileWidget;
	
private:
	void PopulateHiringWorkerList();
	void InitialiseRegionalPool();
	void OnWorkerHired(class UWorkerData* Worker);
	void OnRegionalPoolChanged();
	
	UPROPERTY()
	TObjectPtr<class ARegionalWorkerPool> CachedRegionalPool;
};
