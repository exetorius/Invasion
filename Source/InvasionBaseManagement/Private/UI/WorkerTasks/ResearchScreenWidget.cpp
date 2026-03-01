// CopyrightNotice


#include "UI/WorkerTasks/ResearchScreenWidget.h"

#include "Components/ScrollBox.h"
#include "Controller/ManagementPlayerController.h"
#include "Core/BaseManagerState.h"
#include "Data/TaskTypes.h"
#include "Data/WorkerData.h"
#include "Data/WorkerTypes.h"
#include "UI/ManagementHUD.h"
#include "UI/ManagementUITypes.h"
#include "UI/Tiles/TaskTileWidget.h"

void UResearchScreenWidget::OnScreenDataReady()
{
	InitialiseResearchScreen();	
}

void UResearchScreenWidget::InitialiseResearchScreen()
{
	BindTaskChangeDelegates();
	PopulateTaskList();	
}

void UResearchScreenWidget::PopulateTaskList()
{
	if (!ensure(TaskListScrollBox)) { return; }
	
	UE_LOG(LogTemp, Log, TEXT("ResearchScreenWidget: Populating task list"));
	
	TaskListScrollBox->ClearChildren();
	
	if (CachedBaseManagerState)
	{
		for (const FBaseTask& Task : CachedBaseManagerState->GetActiveTasks())
		{
			if (Task.TaskType != ETaskType::ETT_Research) { continue; }
			if (UTaskTileWidget* TaskTile = CreateWidget<UTaskTileWidget>(this, TaskTileWidget))
			{
				TaskTile->SetTaskData(Task);
				TaskTile->OnAssignClicked.BindUObject(this, &UResearchScreenWidget::OnAssignClicked);
				TaskTile->OnUnassignClicked.BindUObject(this, &UResearchScreenWidget::OnUnassignClicked);
				TaskListScrollBox->AddChild(TaskTile);		
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ResearchScreenWidget: Could not get BaseManagerState"));
	}
}

void UResearchScreenWidget::BindTaskChangeDelegates()
{
	/* TODO: #8 - PopulateTaskList rebuilds all tiles every 1s driven by OnProgressUpdate timer.
	   Better approach: update individual tile data via SetTaskData() rather than clear + recreate.
	   Requires tiles to expose an Update method and screen to hold references to live tiles. */ 
	CachedBaseManagerState->OnTasksChanged.AddUObject(this, &UResearchScreenWidget::PopulateTaskList);
}

void UResearchScreenWidget::OnAssignClicked(FGuid TaskID)
{
	if (!ensure(CachedManagementHUD)) { return; }

	CachedManagementHUD->ShowWorkerPane(
		CachedBaseManagerState,
		EWorkerRole::EWRO_Scientist,
		TaskID,
		FOnAssignClicked::CreateUObject(this, &UResearchScreenWidget::OnWorkerAssigned));
}

void UResearchScreenWidget::OnWorkerAssigned(UWorkerData* Worker, FGuid TaskID)
{
	if (!ensure(CachedPlayerController)) { return; }

	CachedPlayerController->Server_RequestAssignWorker(Worker, TaskID);
	CachedManagementHUD->HideWorkerPane();
}

void UResearchScreenWidget::OnUnassignClicked(FGuid TaskID)
{
	if (CachedBaseManagerState)
	{
		for (const FBaseTask& Task : CachedBaseManagerState->GetActiveTasks())
		{
			if (Task.TaskID == TaskID && Task.AssignedWorkerIDs.Num() > 0)
			{
				// Get the last added worker
				if (UWorkerData* WorkerToRemove = CachedBaseManagerState->FindWorkerByGUID(Task.AssignedWorkerIDs[Task.AssignedWorkerIDs.Num() - 1]))
				{
					if (AManagementPlayerController* PC = Cast<AManagementPlayerController>(GetOwningPlayer()))
					{
						UE_LOG(LogTemp, Log, TEXT("ResearchScreenWidget: Unassigning worker from task"));
						PC->Server_RequestUnassignWorker(WorkerToRemove, TaskID);
					}
				}		
			}
		}	
	}
}
