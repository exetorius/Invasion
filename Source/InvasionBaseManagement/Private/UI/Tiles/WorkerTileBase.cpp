// CopyrightNotice

#include "UI/Tiles/WorkerTileBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UWorkerTileBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensure(ActionButton))
	{
		ActionButton->OnClicked.AddDynamic(this, &UWorkerTileBase::OnActionButtonClicked);
	}
}

void UWorkerTileBase::SetWorkerData(UWorkerData* Worker)
{
	WorkerData = Worker;

	if (WorkerData)
	{
		OnWorkerDataSet(WorkerData);
	}
}

void UWorkerTileBase::SetActionLabel(const FText& Label)
{
	if (ensure(ActionLabelText))
	{
		ActionLabelText->SetText(Label);
	}
}

void UWorkerTileBase::OnActionButtonClicked()
{
	OnActionClicked.ExecuteIfBound(WorkerData);
}
