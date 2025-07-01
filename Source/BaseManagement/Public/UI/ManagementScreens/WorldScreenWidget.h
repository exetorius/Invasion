// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/ManagementHUD.h"
#include "WorldScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class BASEMANAGEMENT_API UWorldScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnWorldButtonClicked, EManagementView);
	FOnWorldButtonClicked OnWorldButtonClicked;

protected:
	UFUNCTION(BlueprintCallable)
	void OnWorldButtonClicked_Implemented(const EManagementView View) const;
};
