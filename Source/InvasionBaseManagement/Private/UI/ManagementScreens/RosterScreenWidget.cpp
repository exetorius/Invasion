// CopyrightNotice


#include "UI/ManagementScreens/RosterScreenWidget.h"
#include "UI/ManagementScreens/Roster/RosterWorkerTileWidget.h"
#include "Core/BaseManagerState.h"
#include "Controller/ManagementPlayerController.h"
#include "Components/ScrollBox.h"
#include "GameFramework/PlayerState.h"


void URosterScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Populate the worker list when the screen is constructed
	PopulateWorkerList();
	
	// Bind to roster changes RepNotify
	BindWorkerRosterChangeEvents();	
}

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

	// Get player's BaseManagerState
	if (AManagementPlayerController* PC = Cast<AManagementPlayerController>(GetOwningPlayer()))
	{
		CachedBaseManagerState = PC->GetBaseManagerState();

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
			UE_LOG(LogTemp, Warning, TEXT("RosterScreenWidget: Could not get BaseManagerState from PlayerController"));
		}
	}
}

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