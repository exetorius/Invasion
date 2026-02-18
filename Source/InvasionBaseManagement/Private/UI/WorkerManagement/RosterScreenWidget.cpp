// CopyrightNotice


#include "UI/WorkerManagement/RosterScreenWidget.h"
#include "UI/WorkerManagement/RosterWorkerTileWidget.h"
#include "Core/BaseManagerState.h"
#include "Controller/ManagementPlayerController.h"
#include "Components/ScrollBox.h"


void URosterScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Populate the worker list when the screen is constructed
	PopulateWorkerList();
	
	// Bind to roster changes RepNotify
	BindWorkerRosterChangeEvents();	
}

//TODO: Comb this class for inconsistencies like this redundant function call
void URosterScreenWidget::RefreshWorkerList()
{
	PopulateWorkerList();
}

void URosterScreenWidget::OnWorkerRosterUpdated()
{
	UE_LOG(LogTemp, Log, TEXT("RosterScreenWidget: Worker roster updated, refreshing UI"));   
	RefreshWorkerList();
}

void URosterScreenWidget::PopulateWorkerList()
{
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

//TODO: Parent class now has a InitialiseScreenData function to cache the base manager. Remove the lower half of this
void URosterScreenWidget::BindWorkerRosterChangeEvents()
{	
	if (CachedBaseManagerState)
	{
		CachedBaseManagerState->OnWorkerRosterChanged.AddUObject(this, &URosterScreenWidget::OnWorkerRosterUpdated);
		return;
	}

	if (AManagementPlayerController* PC = Cast<AManagementPlayerController>(GetOwningPlayer()))
	{
		if (ABaseManagerState* BaseState = PC->GetBaseManagerState())
		{
			BaseState->OnWorkerRosterChanged.AddUObject(this, &URosterScreenWidget::OnWorkerRosterUpdated);
		}
	}
}