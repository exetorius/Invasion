// CopyrightNotice


#include "UI/ManagementScreens/ResearchScreenWidget.h"

#include "Components/ScrollBox.h"
#include "Controller/ManagementPlayerController.h"
#include "Core/BaseManagerState.h"
#include "Data/TaskTypes.h"
#include "UI/WorkerTasks/TaskTileWidget.h"

void UResearchScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	InitialiseResearchScreen();	
}

void UResearchScreenWidget::InitialiseResearchScreen()
{
	if (!CachedBaseManagerState)
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UResearchScreenWidget::InitialiseResearchScreen);
		return;
	}
	BindTaskChangeDelegates();
	PopulateTaskList();	
}

void UResearchScreenWidget::PopulateTaskList()
{
	if (!TaskListScrollBox)
	{
		UE_LOG(LogTemp, Error, TEXT("ResearchScreenWidget: TaskListScrollBox is null - ensure it's bound in Blueprint"));
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("ResearchScreenWidget: Populating task list"));
	
	TaskListScrollBox->ClearChildren();
	
	if (CachedBaseManagerState)
	{
		for (const FBaseTask& Task : CachedBaseManagerState->ActiveTasks)
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
	// TODO: Future, check for research/scientists only instead? Could be a separate list from soldiers and engineers 
	// TODO: Select specific worker rather than grabbing first idle worker
	if (CachedBaseManagerState && CachedBaseManagerState->WorkerRoster.Num() > 0)
	{				
		TArray<UWorkerData*> WorkerRoster = CachedBaseManagerState->WorkerRoster;
		for (UWorkerData* Worker : WorkerRoster)
		{
			if (Worker->Role == EWorkerRole::EWRO_Scientist && Worker->CurrentStatus == EWorkerStatus::EWS_Idle)
			{
				if (AManagementPlayerController* PC = Cast<AManagementPlayerController>(GetOwningPlayer()))
				{
					UE_LOG(LogTemp, Log, TEXT("ResearchScreenWidget: Assigning worker to task"));
					PC->Server_RequestAssignWorker(Worker, TaskID);
					return;
				}				
			}
		}		
	}
}

void UResearchScreenWidget::OnUnassignClicked(FGuid TaskID)
{
	if (CachedBaseManagerState)
	{
		for (FBaseTask& Task : CachedBaseManagerState->ActiveTasks)
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
