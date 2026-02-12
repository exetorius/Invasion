// CopyrightNotice

#pragma once

#include "Blueprint/UserWidget.h"
#include "UI/ManagementHUD.h"
#include "BaseManagementScreenWidget.generated.h"

 /**
 * Base management screen widget class that all other screen widgets inherit from.
 */
UCLASS()
class BASEMANAGEMENT_API UBaseManagementScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnNavigationButtonPressed, EManagementView);
	FOnNavigationButtonPressed OnNavigationButtonPressed;
	
protected:
	UFUNCTION(BlueprintCallable)
	void NavigationButtonPressed(const EManagementView View) const;
};
