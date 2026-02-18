// CopyrightNotice

#include "UI/WorkerManagement//RosterWorkerTileWidget.h"
#include "Data/WorkerData.h"

void URosterWorkerTileWidget::OnFireButtonClicked()
{
	OnFireClicked.ExecuteIfBound( WorkerData);
}

void URosterWorkerTileWidget::SetWorkerData(UWorkerData* Worker)
{
	WorkerData = Worker;

	if (WorkerData)
	{
		// Call Blueprint event to update UI
		OnWorkerDataSet(WorkerData);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RosterWorkerTileWidget: SetWorkerData called with null worker"));
	}
}
