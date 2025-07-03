#include "UI/ManagementHUD.h"
#include "Components/WidgetSwitcher.h"
#include "UI/ManagementScreens/BaseManagementScreenWidget.h"



void UManagementHUD::NativeConstruct()
{
	Super::NativeConstruct();

	// Initialise Map and Delegates
	SetupViewMap();
	BindNavigationDelegates();

	// Start on World overview
	SwitchToView(EManagementView::EMV_World);
}

void UManagementHUD::SetupViewMap()
{
	ViewMap.Add(EManagementView::EMV_World, WBP_WorldScreen);
	ViewMap.Add(EManagementView::EMV_Base, WBP_BaseScreen);
	ViewMap.Add(EManagementView::EMV_Roster, WBP_RosterScreen);
	ViewMap.Add(EManagementView::EMV_Character, WBP_CharacterScreen);
	ViewMap.Add(EManagementView::EMV_Warehouse, WBP_WarehouseScreen);
	ViewMap.Add(EManagementView::EMV_Research, WBP_ResearchScreen);
	ViewMap.Add(EManagementView::EMV_Engineering, WBP_EngineeringScreen);
}

void UManagementHUD::BindNavigationDelegates()
{
	if (WBP_WorldScreen)
	{
		if (UBaseManagementScreenWidget* WorldScreen = Cast<UBaseManagementScreenWidget>(WBP_WorldScreen))
		{
			WorldScreen->OnNavigationButtonPressed.BindUObject(this, &UManagementHUD::SwitchToView);
		}
	}
	
	if (WBP_CharacterScreen)
	{
		if (UBaseManagementScreenWidget* Screen= Cast<UBaseManagementScreenWidget>(WBP_CharacterScreen))
		{
			Screen->OnNavigationButtonPressed.BindUObject(this, &ThisClass::SwitchToView);
		}
	}
}

void UManagementHUD::SwitchToView(EManagementView NewView)
{
	if (!WidgetSwitcher)
	{
		UE_LOG(LogTemp, Error, TEXT("OverlaySwitcher is NULL"));
		return;
	}

	// Search the TMap for the desired widget to display and if valid, display it
	if (UUserWidget** FoundWidget = ViewMap.Find(NewView))
	{
		WidgetSwitcher->SetActiveWidget(*FoundWidget);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No widget found for view %d"), static_cast<int32>(NewView));
	}
}
