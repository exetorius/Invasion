#include "UI/ManagementScreens/BaseManagementScreenWidget.h"

#include "Controller/ManagementPlayerController.h"

void UBaseManagementScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	InitialiseScreenData();
}

void UBaseManagementScreenWidget::NavigationButtonPressed(const EManagementView View) const
{
	OnNavigationButtonPressed.ExecuteIfBound(View);
}

void UBaseManagementScreenWidget::InitialiseScreenData()
{
	// Get player's BaseManagerState
	if (const AManagementPlayerController* PC = Cast<AManagementPlayerController>(GetOwningPlayer()))
	{
		CachedBaseManagerState = PC->GetBaseManagerState();
		
		if (!CachedBaseManagerState)
		{
			if (const UWorld* World = GetWorld())
			{
				World->GetTimerManager().SetTimerForNextTick(this, &UBaseManagementScreenWidget::InitialiseScreenData);
			}			
		}			
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BaseManagementScreenWidget: Could not get PlayerController"));
	}		
}
