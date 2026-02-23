#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManagementUITypes.h"
#include "ManagementHUD.generated.h"

UCLASS()
class INVASIONBASEMANAGEMENT_API UManagementHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	void SwitchToView(EManagementView NewView);	

protected:
	void BindNavigationDelegates();
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWorldScreenWidget> WBP_WorldScreen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UBaseOverviewScreenWidget> WBP_BaseOverviewScreen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class URosterScreenWidget> WBP_RosterScreen;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UHiringScreenWidget> WBP_HiringScreen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCharacterScreenWidget> WBP_CharacterScreen;	

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWarehouseScreenWidget> WBP_WarehouseScreen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UResearchScreenWidget> WBP_ResearchScreen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEngineeringScreenWidget> WBP_EngineeringScreen;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UManagementNavigationWidget> WBP_ButtonBar;

private:
	void SetupViewMap();
	
	UPROPERTY()
	TMap<EManagementView, UUserWidget*> ViewMap;
	
};
