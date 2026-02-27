#include "UI/ManagementScreens/BaseManagementScreenWidget.h"

#include "Controller/ManagementPlayerController.h"

void UBaseManagementScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

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
