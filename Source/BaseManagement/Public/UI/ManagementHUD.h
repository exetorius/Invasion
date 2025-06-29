#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManagementHUD.generated.h"

UENUM()
enum class EManagementView : uint8
{
	EMV_None		UMETA(DisplayName = "None"),
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
	void SwitchToView(EManagementView NewView);	

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UWidgetSwitcher* OverlaySwitcher;

	UPROPERTY(meta = (BindWidget))
	UWidget* Overlay_None;

	UPROPERTY(meta = (BindWidget))
	UWidget* Overlay_World;

	UPROPERTY(meta = (BindWidget))
	UWidget* Overlay_Base;

	UPROPERTY(meta = (BindWidget))
	UWidget* Overlay_Roster;

	UPROPERTY(meta = (BindWidget))
	UWidget* Overlay_Character;	

	UPROPERTY(meta = (BindWidget))
	UWidget* Overlay_Inventory;

	UPROPERTY(meta = (BindWidget))
	UWidget* Overlay_Research;

	UPROPERTY(meta = (BindWidget))
	UWidget* Overlay_Engineering;

private:
	void SetupViewMap();
	
	UPROPERTY()
	TMap<EManagementView, UWidget*> ViewMap;
	
};
