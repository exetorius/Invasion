// CopyrightNotice


#include "UI/WorkerTasks/TaskTileWidget.h"

void UTaskTileWidget::OnAssignButtonClicked()
{
	OnAssignClicked.ExecuteIfBound(TaskData.TaskID);
}

void UTaskTileWidget::OnUnassignButtonClicked()
{
	OnUnassignClicked.ExecuteIfBound(TaskData.TaskID);
}

void UTaskTileWidget::SetTaskData(const FBaseTask& NewTaskData)
{
	TaskData = NewTaskData;
	
	OnTaskDataSet(TaskData);
}
