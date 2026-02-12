// CopyrightNotice


#include "Controller/ManagementPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UI/ManagementHUD.h"
#include "Core/BaseManagerState.h"
#include "GameMode/ManagementGameMode.h"
#include "Kismet/GameplayStatics.h"

void AManagementPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateHUD();
}

void AManagementPlayerController::CreateHUD()
{
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

ABaseManagerState* AManagementPlayerController::GetBaseManagerState() const
{
	// Return cached if available
	if (CachedBaseManagerState)
	{
		return CachedBaseManagerState;
	}

	// Get from GameMode
	if (AManagementGameMode* GameMode = Cast<AManagementGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (PlayerState)
		{
			CachedBaseManagerState = GameMode->GetBaseManagerStateForPlayer(PlayerState);
			return CachedBaseManagerState;
		}
	}

	return nullptr;
}
