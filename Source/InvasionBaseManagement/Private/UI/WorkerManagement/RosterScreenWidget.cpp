// CopyrightNotice


#include "UI/WorkerManagement/RosterScreenWidget.h"
#include "UI/Tiles/RosterWorkerTileWidget.h"
#include "Core/BaseManagerState.h"
#include "PlayerController/ManagementPlayerController.h"
#include "Components/ScrollBox.h"
#include "Subsystems/InvasionCampaignSubsystem.h"

// Button functionality called from BP
void URosterScreenWidget::RefreshWorkerList()
{
	PopulateWorkerList();
}

void URosterScreenWidget::OnScreenDataReady()
{
	InitialiseRosterScreen();	
}

void URosterScreenWidget::OnWorkerRosterUpdated(UWorkerData* Worker)
{
	UE_LOG(LogTemp, Log, TEXT("RosterScreenWidget: Worker roster updated, refreshing UI"));   
	PopulateWorkerList();
}

void URosterScreenWidget::InitialiseRosterScreen()
{
	PopulateWorkerList();	
	BindWorkerRosterChangeEvents();	
}

void URosterScreenWidget::PopulateWorkerList()
{
	// TODO: Display workers in a list by Role - Soldiers, Scientists, Engineers, Medics etc
	if (!ensure(WorkerListScrollBox))	{ return; }
	if (!ensure(CachedCampaignSubsystem)) { return; }

	// Clear existing tiles
	WorkerListScrollBox->ClearChildren();

	const TArray<UWorkerData*>& Workers = CachedCampaignSubsystem->GetRoster();

	UE_LOG(LogTemp, Log, TEXT("RosterScreenWidget: Populating %d workers"), Workers.Num());

	// Create a tile for each worker
	for (UWorkerData* Worker : Workers)
	{
		if (Worker && WorkerTileClass)
		{
			if (URosterWorkerTileWidget* Tile = CreateWidget<URosterWorkerTileWidget>(this, WorkerTileClass))
			{
				Tile->SetWorkerData(Worker);
				Tile->SetActionLabel(FText::FromString("Fire"));
				Tile->OnActionClicked.BindUObject(this, &URosterScreenWidget::OnWorkerFired);
				WorkerListScrollBox->AddChild(Tile);
			}
		}
	}
}

void URosterScreenWidget::BindWorkerRosterChangeEvents()
{	
	CachedCampaignSubsystem->OnWorkerAdded.AddDynamic(this, &URosterScreenWidget::OnWorkerRosterUpdated);
	CachedCampaignSubsystem->OnWorkerRemoved.AddDynamic(this, &URosterScreenWidget::OnWorkerRosterUpdated);
}

void URosterScreenWidget::OnWorkerFired( UWorkerData* Worker)
{
	if (!Worker) { return;}
	
	if (AManagementPlayerController* PC = Cast<AManagementPlayerController>(GetOwningPlayer()))
	{
		PC->Server_RequestFireWorker(Worker);
	}
}