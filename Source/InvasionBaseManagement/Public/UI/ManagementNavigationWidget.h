// CopyrightNotice

#pragma once

#include "Blueprint/UserWidget.h"
#include "UI/ManagementUITypes.h"
#include "ManagementNavigationWidget.generated.h"

/**
 * Lightweight base class for any widget that needs to fire navigation events.
 * Holds the navigation delegate only — no screen data or state concerns.
 * ButtonBar and BaseManagementScreenWidget both inherit from this.
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UManagementNavigationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnNavigationButtonPressed, EManagementView);
	FOnNavigationButtonPressed OnNavigationButtonPressed;

protected:
	UFUNCTION(BlueprintCallable)
	void NavigationButtonPressed(const EManagementView View) const;
};
