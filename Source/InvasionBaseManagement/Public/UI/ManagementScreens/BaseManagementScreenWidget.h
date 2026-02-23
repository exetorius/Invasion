// CopyrightNotice

#pragma once

#include "UI/ManagementNavigationWidget.h"
#include "BaseManagementScreenWidget.generated.h"

 /**
 * Base management screen widget class that all other screen widgets inherit from.
 * Extends UManagementNavigationWidget with screen data and state concerns.
 */
UCLASS()
class INVASIONBASEMANAGEMENT_API UBaseManagementScreenWidget : public UManagementNavigationWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	void InitialiseScreenData();
	
	virtual void OnScreenDataReady();
	
	UPROPERTY()
	TObjectPtr<class ABaseManagerState> CachedBaseManagerState;
};
