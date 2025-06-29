#include "UI/ManagementHUD.h"
#include "Components/WidgetSwitcher.h"

void UManagementHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetupViewMap();

	// Start on World overview
	SwitchToView(EManagementView::EMV_Research);
}

void UManagementHUD::SetupViewMap()
{
	ViewMap.Add(EManagementView::EMV_None, Overlay_None);
	ViewMap.Add(EManagementView::EMV_World, Overlay_World);
	ViewMap.Add(EManagementView::EMV_Base, Overlay_Base);
	ViewMap.Add(EManagementView::EMV_Roster, Overlay_Roster);
	ViewMap.Add(EManagementView::EMV_Character, Overlay_Character);
	ViewMap.Add(EManagementView::EMV_Inventory, Overlay_Inventory);
	ViewMap.Add(EManagementView::EMV_Research, Overlay_Research);
	ViewMap.Add(EManagementView::EMV_Engineering, Overlay_Engineering);
}

void UManagementHUD::SwitchToView(EManagementView NewView)
{
	if (!OverlaySwitcher)
	{
		UE_LOG(LogTemp, Error, TEXT("OverlaySwitcher is NULL"));
		return;
	}

	// Search the TMap for the desired widget to display and if valid, display it
	if (UWidget** FoundWidget = ViewMap.Find(NewView))
	{
		OverlaySwitcher->SetActiveWidget(*FoundWidget);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No widget found for view %d"), static_cast<int32>(NewView));
	}
}


