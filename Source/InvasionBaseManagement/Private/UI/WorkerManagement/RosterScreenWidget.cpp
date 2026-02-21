// CopyrightNotice


#include "UI/WorkerManagement/RosterScreenWidget.h"
#include "UI/WorkerManagement/RosterWorkerTileWidget.h"
#include "Core/BaseManagerState.h"
#include "Controller/ManagementPlayerController.h"
#include "Components/ScrollBox.h"


void URosterScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitialiseRosterScreen();	
}

// Button functionality called from BP
void URosterScreenWidget::RefreshWorkerList()
{
	PopulateWorkerList();
}

void URosterScreenWidget::OnWorkerRosterUpdated()
{
	UE_LOG(LogTemp, Log, TEXT("RosterScreenWidget: Worker roster updated, refreshing UI"));   
	PopulateWorkerList();
}

void URosterScreenWidget::InitialiseRosterScreen()
{
	if (!CachedBaseManagerState)
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &URosterScreenWidget::InitialiseRosterScreen);
		return;
	}
	PopulateWorkerList();	
	BindWorkerRosterChangeEvents();	
}

void URosterScreenWidget::PopulateWorkerList()
{
	// TODO: Display workers in a list by Role - Soldiers, Scientists, Engineers, Medics etc
	if (!WorkerListScrollBox)
	{
		UE_LOG(LogTemp, Error, TEXT("RosterScreenWidget: WorkerListScrollBox is null - ensure it's bound in Blueprint"));
		return;
	}

	// Clear existing tiles
	WorkerListScrollBox->ClearChildren();

	if (CachedBaseManagerState)
	{
		const TArray<UWorkerData*>& Workers = CachedBaseManagerState->GetAllWorkers();

		UE_LOG(LogTemp, Log, TEXT("RosterScreenWidget: Populating %d workers"), Workers.Num());

		// Create a tile for each worker
		for (UWorkerData* Worker : Workers)
		{
			if (Worker && WorkerTileClass)
			{
				if (URosterWorkerTileWidget* Tile = CreateWidget<URosterWorkerTileWidget>(this, WorkerTileClass))
				{
					Tile->SetWorkerData(Worker);
					Tile->OnFireClicked.BindUObject(this, &URosterScreenWidget::OnWorkerFired);
					WorkerListScrollBox->AddChild(Tile);
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RosterScreenWidget: Could not get BaseManagerState"));
	}
}

void URosterScreenWidget::BindWorkerRosterChangeEvents()
{	
	CachedBaseManagerState->OnWorkerRosterChanged.AddUObject(this, &URosterScreenWidget::OnWorkerRosterUpdated);
}

void URosterScreenWidget::OnWorkerFired( UWorkerData* Worker)
{
	if (!Worker) { return;}
	
	if (AManagementPlayerController* PC = Cast<AManagementPlayerController>(GetOwningPlayer()))
	{
		PC->Server_RequestFireWorker(Worker);
	}
}