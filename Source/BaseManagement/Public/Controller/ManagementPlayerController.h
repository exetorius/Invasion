// CopyrightNotice

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ManagementPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BASEMANAGEMENT_API AManagementPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UManagementHUD> HUDClass;

private:
	UPROPERTY()
	TObjectPtr<UManagementHUD> HUD;
};
