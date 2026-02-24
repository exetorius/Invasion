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
	// Refresh the worker list from BaseManagerState
	UFUNCTION(BlueprintCallable, Category = "Roster")
	void RefreshWorkerList();
	
protected:
	virtual void OnScreenDataReady() override;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UHiringWorkerTileWidget> WorkerTileWidget;
	
private:
	void PopulateHiringWorkerList();
	void InitialiseRegionalPool();
	void OnWorkerHired(class UWorkerData* Worker);
	void OnRegionalPoolChanged();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UScrollBox> WorkerListScrollBox;
	
	UPROPERTY()
	TObjectPtr<class ARegionalWorkerPool> CachedRegionalPool;
};
