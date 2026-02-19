#include "UI/ManagementHUD.h"
#include "UI/ManagementScreens/BaseScreenWidget.h"
#include "UI/ManagementScreens/CharacterScreenWidget.h"
#include "UI/ManagementScreens/EngineeringScreenWidget.h"
#include "UI/ManagementScreens/WorldScreenWidget.h"
#include "UI/WorkerManagement/RosterScreenWidget.h"
#include "UI/WorkerManagement/HiringScreenWidget.h"
#include "UI/ManagementScreens/WarehouseScreenWidget.h"
#include "UI/ManagementScreens/ResearchScreenWidget.h"
#include "UI/ManagementNavigationWidget.h"

#include "Components/WidgetSwitcher.h"



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
	ViewMap.Add(EManagementView::EMV_Hiring, WBP_HiringScreen);
	ViewMap.Add(EManagementView::EMV_Character, WBP_CharacterScreen);
	ViewMap.Add(EManagementView::EMV_Warehouse, WBP_WarehouseScreen);
	ViewMap.Add(EManagementView::EMV_Research, WBP_ResearchScreen);
	ViewMap.Add(EManagementView::EMV_Engineering, WBP_EngineeringScreen);
}

void UManagementHUD::BindNavigationDelegates()
{
	/*
	for (const TTuple<EManagementView, UUserWidget*>& ScreenPair : ViewMap)
	{
		if (UBaseManagementScreenWidget* Screen = Cast<UBaseManagementScreenWidget>(ScreenPair.Value))
		{
			Screen->OnNavigationButtonPressed.BindUObject(this, &UManagementHUD::SwitchToView);
		}
	}
	*/
	if (WBP_ButtonBar)
	{
		WBP_ButtonBar->OnNavigationButtonPressed.BindUObject(this, &UManagementHUD::SwitchToView);
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
