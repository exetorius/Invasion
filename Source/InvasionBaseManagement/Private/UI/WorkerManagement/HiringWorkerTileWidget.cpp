// CopyrightNotice


#include "UI/WorkerManagement/HiringWorkerTileWidget.h"

void UHiringWorkerTileWidget::SetWorkerData(UWorkerData* Worker)
{
	WorkerData = Worker;	
	
	if (WorkerData)
	{
		OnWorkerDataSet(WorkerData);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HiringWorkerTileWidget: SetWorkerData called with null worker"));
	}
}

void UHiringWorkerTileWidget::OnHireButtonClicked()
{
	OnHireClicked.ExecuteIfBound(WorkerData);
}
