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
	EMV_Inventory	UMETA(DisplayName = "Inventory"),
	EMV_Research	UMETA(DisplayName = "Research"),
	EMV_Engineering UMETA(DisplayName = "Engineering"),

	EMV_DefaultMAX	UMETA(DisplayName="MAX")
};

UCLASS()
class BASEMANAGEMENT_API UManagementHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	void SwitchToView(EManagementView NewView);	

protected:
	void BindNavigationDelegates();
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* WBP_WorldScreen;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* WBP_BaseScreen;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* WBP_RosterScreen;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* WBP_CharacterScreen;	

	UPROPERTY(meta = (BindWidget))
	UUserWidget* WBP_InventoryScreen;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* WBP_ResearchScreen;

	UPROPERTY(meta = (BindWidget))
	UUserWidget* WBP_EngineeringScreen;

private:
	void SetupViewMap();
	
	UPROPERTY()
	TMap<EManagementView, UUserWidget*> ViewMap;
	
};
