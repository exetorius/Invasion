// CopyrightNotice


#include "Controller/ManagementPlayerController.h"
#include <Blueprint/UserWidget.h>

#include "UI/ManagementHUD.h"

void AManagementPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalPlayerController())
	{
		if (HUDClass)
		{
			HUD = CreateWidget<UManagementHUD>(this, HUDClass);
			if (HUD)
			{
				HUD->AddToViewport();
				
				FInputModeUIOnly InputMode;
				InputMode.SetWidgetToFocus(HUD->TakeWidget());
				SetInputMode(InputMode);
				bShowMouseCursor = true;
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ManagementPlayerController: HUDClass is not set!"));
		}
	}	
}
