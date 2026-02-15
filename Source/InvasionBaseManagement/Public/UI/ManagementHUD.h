#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManagementHUD.generated.h"

UENUM(BlueprintType)
enum class EManagementView : uint8
{
	EMV_World		UMETA(DisplayName = "World"),
	EMV_Base		UMETA(DisplayName = "Base"),
	EMV_Roster		UMETA(DisplayName = "Roster"),
	EMV_Character	UMETA(DisplayName = "Character"),
	EMV_Warehouse	UMETA(DisplayName = "Warehouse"),
	EMV_Research	UMETA(DisplayName = "Research"),
	EMV_Engineering UMETA(DisplayName = "Engineering"),
	
	EMV_ButtonBar	UMETA(DisplayName = "Button Bar"),
	EMV_DefaultMAX	UMETA(DisplayName="MAX")
};

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
	TObjectPtr<UUserWidget> WBP_WorldScreen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> WBP_BaseScreen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> WBP_RosterScreen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> WBP_CharacterScreen;	

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> WBP_WarehouseScreen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> WBP_ResearchScreen;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> WBP_EngineeringScreen;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> WBP_ButtonBar;

private:
	void SetupViewMap();
	
	UPROPERTY()
	TMap<EManagementView, UUserWidget*> ViewMap;
	
};
