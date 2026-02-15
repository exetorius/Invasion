// CopyrightNotice


#include "Controller/ManagementPlayerController.h"

#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "UI/ManagementHUD.h"
#include "Core/BaseManagerState.h"
#include "GameMode/ManagementGameMode.h"
#include "Kismet/GameplayStatics.h"

void AManagementPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CheckPlayerReady();
}

void AManagementPlayerController::CheckPlayerReady()
{
	if (CachedBaseManagerState)
	{
		CreateHUD();
		return;
	}
	
	ABaseManagerState* ManagerState = GetBaseManagerState();
	if (!ManagerState)
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &AManagementPlayerController::CheckPlayerReady);
		return;
	}

	// Check that the WorkerData inside has actually replicated
	if (ManagerState->GetAllWorkers().IsEmpty())
	{
		GetWorldTimerManager().SetTimerForNextTick(this, &AManagementPlayerController::CheckPlayerReady);
		return;
	}

	// Everything is replicated and ready
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

				const FInputModeUIOnly InputMode;
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

	if (!PlayerState)
	{
		return nullptr;
	}

	// Server: Use GameMode lookup (faster)
	if (HasAuthority())
	{
		if (AManagementGameMode* GameMode = Cast<AManagementGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			CachedBaseManagerState = GameMode->GetBaseManagerStateForPlayer(PlayerState);
			return CachedBaseManagerState;
		}
	}
	// Client: Search through replicated BaseManagerState actors
	else
	{
		for (TActorIterator<ABaseManagerState> It(GetWorld()); It; ++It)
		{
			ABaseManagerState* State = *It;
			if (State && State->OwningPlayerState == PlayerState)
			{
				CachedBaseManagerState = State;
				UE_LOG(LogTemp, Log, TEXT("ManagementPlayerController: Client found BaseManagerState via TActorIterator"));
				return CachedBaseManagerState;
			}
		}
	}

	return nullptr;
}
