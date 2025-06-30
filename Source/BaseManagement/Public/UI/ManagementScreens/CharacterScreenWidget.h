// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	UFUNCTION()
	void InitializeManagementHUD(UManagementHUD* InHUD) { ManagementHUD = InHUD; }

private:
	UPROPERTY(BlueprintReadOnly, Category="UI", meta=(AllowPrivateAccess=true))
	TObjectPtr<UManagementHUD> ManagementHUD;
};
