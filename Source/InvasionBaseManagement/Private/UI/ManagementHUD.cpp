#include "UI/ManagementHUD.h"
#include "UI/ManagementScreens/BaseOverviewScreenWidget.h"
#include "UI/ManagementScreens/CharacterScreenWidget.h"
#include "UI/WorkerTasks/EngineeringScreenWidget.h"
#include "UI/ManagementScreens/WorldScreenWidget.h"
#include "UI/WorkerManagement/RosterScreenWidget.h"
#include "UI/WorkerManagement/HiringScreenWidget.h"
#include "UI/ManagementScreens/WarehouseScreenWidget.h"
#include "UI/WorkerTasks/ResearchScreenWidget.h"
#include "UI/ManagementNavigationWidget.h"

#include "Components/WidgetSwitcher.h"
#include "UI/WorkerManagement/WorkerPaneWidget.h"


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
	ViewMap.Add(EManagementView::EMV_BaseOverview, WBP_BaseOverviewScreen);
	ViewMap.Add(EManagementView::EMV_Roster, WBP_RosterScreen);
	ViewMap.Add(EManagementView::EMV_Hiring, WBP_HiringScreen);
	ViewMap.Add(EManagementView::EMV_Character, WBP_CharacterScreen);
	ViewMap.Add(EManagementView::EMV_Warehouse, WBP_WarehouseScreen);
	ViewMap.Add(EManagementView::EMV_Research, WBP_ResearchScreen);
	ViewMap.Add(EManagementView::EMV_Engineering, WBP_EngineeringScreen);
}

// TODO: Implement navigation button binding for each screen when implementing subscreen navigation
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

void UManagementHUD::ShowWorkerPane(ABaseManagerState* BaseManagerState, EWorkerRole WorkerRole, FGuid TaskID, FOnAssignClicked Callback)
{
	if (!ensure(WBP_WorkerPaneWidget)) { return; }

	WBP_WorkerPaneWidget->OnAssignClicked = Callback;
	WBP_WorkerPaneWidget->ShowWorkerList(BaseManagerState, WorkerRole, TaskID);
	WBP_WorkerPaneWidget->SetVisibility(ESlateVisibility::Visible);
}

void UManagementHUD::HideWorkerPane()
{
	if (!ensure(WBP_WorkerPaneWidget)) { return; }
	
	WBP_WorkerPaneWidget->HideWorkerList();
	WBP_WorkerPaneWidget->SetVisibility(ESlateVisibility::Collapsed);
}
