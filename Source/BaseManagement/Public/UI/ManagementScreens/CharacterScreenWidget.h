// CopyrightNotice

#pragma once

#include "Blueprint/UserWidget.h"
#include "UI/ManagementHUD.h"
#include "CharacterScreenWidget.generated.h"

class UManagementHUD;
/**
 * 
 */
UCLASS()
class BASEMANAGEMENT_API UCharacterScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DELEGATE_OneParam(FOnBackRequested, EManagementView);
	FOnBackRequested OnBackRequested;
	
protected:
	UFUNCTION(BlueprintCallable)
	void OnBackRequested_Implementation(const EManagementView View) const;
};
