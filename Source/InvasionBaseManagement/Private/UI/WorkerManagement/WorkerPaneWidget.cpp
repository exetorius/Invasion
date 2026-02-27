// CopyrightNotice


#include "UI/WorkerManagement/WorkerPaneWidget.h"

#include "Components/ScrollBox.h"
#include "Core/BaseManagerState.h"
#include "Data/WorkerData.h"
#include "Data/WorkerTypes.h"
#include "UI/Tiles/WorkerTileBase.h"

void UWorkerPaneWidget::ShowWorkerList(ABaseManagerState* BaseManagerState, EWorkerRole WorkerType, FGuid InTaskID)
{
	CachedBaseManagerState = BaseManagerState;
	CachedRoleFilter = WorkerType;
	CachedTaskID = InTaskID;
	
	CachedBaseManagerState->OnWorkerRosterChanged.AddUObject(this, &UWorkerPaneWidget::InitialiseWorkerPane);

	InitialiseWorkerPane();
}

void UWorkerPaneWidget::HideWorkerList()
{
	if (!ensure(WorkerList)) { return; }
	WorkerList->ClearChildren();
	if (CachedBaseManagerState)
	{
		CachedBaseManagerState->OnWorkerRosterChanged.RemoveAll(this);
	}
}

void UWorkerPaneWidget::InitialiseWorkerPane()
{
	if (!ensure(WorkerList)) { return; }
	if (!ensure(CachedBaseManagerState)) { return; }

	if (!WorkerTileWidget)
	{
		UE_LOG(LogTemp, Error, TEXT("WorkerPaneWidget: WorkerTileWidget class not set — assign it in Blueprint defaults"));
		return;
	}

	WorkerList->ClearChildren();

	for (UWorkerData* Worker : CachedBaseManagerState->GetAllWorkers())
	{
		if (!Worker) { continue; }
		if (Worker->GetRole() != CachedRoleFilter) { continue; }
		if (Worker->GetCurrentStatus() != EWorkerStatus::EWS_Idle) { continue; }

		if (UWorkerTileBase* Tile = CreateWidget<UWorkerTileBase>(this, WorkerTileWidget))
		{
			Tile->SetWorkerData(Worker);
			Tile->SetActionLabel(FText::FromString("Assign"));
			Tile->OnActionClicked.BindUObject(this, &UWorkerPaneWidget::OnWorkerSelected);
			WorkerList->AddChild(Tile);
		}
	}
}

void UWorkerPaneWidget::OnWorkerSelected(UWorkerData* Worker)
{
	OnAssignClicked.ExecuteIfBound(Worker, CachedTaskID);
}
