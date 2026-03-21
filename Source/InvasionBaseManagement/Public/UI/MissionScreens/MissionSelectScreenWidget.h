// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "UI/ManagementScreens/BaseManagementScreenWidget.h"
#include "MissionSelectScreenWidget.generated.h"

class UScrollBox;
class URosterWorkerTileWidget;
class UWorkerData;
class UMissionBridgeSubsystem;

/**
 * 
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UMissionSelectScreenWidget : public UBaseManagementScreenWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Launch();
	
	UFUNCTION(BlueprintCallable)
	void SelectSoldier(UWorkerData* SelectedSoldier);
	UFUNCTION(BlueprintCallable)
	void DeselectSoldier(UWorkerData* DeselectedSoldier);
	
protected:
	virtual void OnScreenDataReady() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	int32 MaxSquadSize = 6;
	UPROPERTY()
	TArray<TObjectPtr<UWorkerData>> AvailableSoldiers;
	UPROPERTY()
	TArray<TObjectPtr<UWorkerData>> SelectedSoldiers;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> TacticalLevel;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URosterWorkerTileWidget> WorkerTileWidget;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> AvailableSoldiersScrollBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> SelectedSoldiersScrollBox;
	
	void PopulateWorkerList();
	
	void PopulateAvailableSoldiersList();
	void PopulateSelectedSoldiersList();
	
	void OnWorkerRosterUpdated();
};
