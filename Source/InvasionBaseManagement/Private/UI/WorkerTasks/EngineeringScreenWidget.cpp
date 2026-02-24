// CopyrightNotice


#include "UI/WorkerTasks/EngineeringScreenWidget.h"

#include "Components/ScrollBox.h"
#include "Controller/ManagementPlayerController.h"
#include "Core/BaseManagerState.h"
#include "Data/TaskTypes.h"
#include "UI/WorkerTasks/TaskTileWidget.h"

void UEngineeringScreenWidget::OnScreenDataReady()
{
	InitialiseEngineeringScreen();
}

void UEngineeringScreenWidget::InitialiseEngineeringScreen()
{
	BindTaskChangeDelegates();
	PopulateTaskList();	
}

void UEngineeringScreenWidget::PopulateTaskList()
{
	if (!ensure(TaskListScrollBox))	{ return; }
	
	UE_LOG(LogTemp, Log, TEXT("EngineeringScreenWidget: Populating task list"));
	
	TaskListScrollBox->ClearChildren();
	
	if (CachedBaseManagerState)
	{
		for (const FBaseTask& Task : CachedBaseManagerState->GetActiveTasks())
		{
			if (Task.TaskType != ETaskType::ETT_Engineering) { continue; }
			if (UTaskTileWidget* TaskTile = CreateWidget<UTaskTileWidget>(this, TaskTileWidget))
			{
				TaskTile->SetTaskData(Task);
				TaskTile->OnAssignClicked.BindUObject(this, &UEngineeringScreenWidget::OnAssignClicked);
				TaskTile->OnUnassignClicked.BindUObject(this, &UEngineeringScreenWidget::OnUnassignClicked);
				TaskListScrollBox->AddChild(TaskTile);		
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EngineeringScreenWidget: Could not get BaseManagerState"));
	}
}

void UEngineeringScreenWidget::BindTaskChangeDelegates()
{
	/* TODO: #8 - PopulateTaskList rebuilds all tiles every 1s driven by OnProgressUpdate timer.
	   Better approach: update individual tile data via SetTaskData() rather than clear + recreate.
	   Requires tiles to expose an Update method and screen to hold references to live tiles. */ 
	CachedBaseManagerState->OnTasksChanged.AddUObject(this, &UEngineeringScreenWidget::PopulateTaskList);
}

void UEngineeringScreenWidget::OnAssignClicked(FGuid TaskID)
{
	// TODO: Future, check for research/scientists only instead? Could be a separate list from soldiers and engineers 
	// TODO: Select specific worker rather than grabbing first idle worker
	if (CachedBaseManagerState && CachedBaseManagerState->GetAllWorkers().Num() > 0)
	{				
		TArray<UWorkerData*> WorkerRoster = CachedBaseManagerState->GetAllWorkers();
		for (UWorkerData* Worker : WorkerRoster)
		{
			if (Worker->GetRole() == EWorkerRole::EWRO_Engineer && Worker->GetCurrentStatus() == EWorkerStatus::EWS_Idle)
			{
				if (AManagementPlayerController* PC = Cast<AManagementPlayerController>(GetOwningPlayer()))
				{
					UE_LOG(LogTemp, Log, TEXT("EngineeringScreenWidget: Assigning worker to task"));
					PC->Server_RequestAssignWorker(Worker, TaskID);
					return;
				}				
			}
		}		
	}
}

void UEngineeringScreenWidget::OnUnassignClicked(FGuid TaskID)
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
						UE_LOG(LogTemp, Log, TEXT("EngineeringScreenWidget: Unassigning worker from task"));
						PC->Server_RequestUnassignWorker(WorkerToRemove, TaskID);
					}
				}		
			}
		}	
	}
}
