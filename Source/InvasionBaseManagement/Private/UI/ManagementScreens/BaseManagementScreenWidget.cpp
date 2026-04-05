#include "UI/ManagementScreens/BaseManagementScreenWidget.h"

#include "PlayerController/ManagementPlayerController.h"

void UBaseManagementScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("BaseManagementScreenWidget: Constructed"));
	InitialiseScreenData();
}

void UBaseManagementScreenWidget::InitialiseScreenData()
{
	// Get player's BaseManagerState
	if (AManagementPlayerController* PC = Cast<AManagementPlayerController>(GetOwningPlayer()))
	{
		CachedPlayerController = PC;
		CachedBaseManagerState = PC->GetBaseManagerState();
		CachedManagementHUD = PC->GetManagementHUD();
		CachedCampaignSubsystem = PC->GetCampaignSubsystem();
		
		if (!CachedBaseManagerState)
		{
			if (const UWorld* World = GetWorld())
			{
				World->GetTimerManager().SetTimerForNextTick(this, &UBaseManagementScreenWidget::InitialiseScreenData);
			}			
		}
		else
		{
			OnScreenDataReady();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseManagementScreenWidget: Could not get PlayerController"));
	}		
}

void UBaseManagementScreenWidget::OnScreenDataReady()
{
}
