// CopyrightNotice

#include "UI/ManagementScreens/BaseOverviewScreenWidget.h"
#include "Core/BaseManagerState.h"
#include "Data/WorkerData.h"
#include "Components/TextBlock.h"

void UBaseOverviewScreenWidget::OnScreenDataReady()
{
	InitialiseOverviewScreen();
}

void UBaseOverviewScreenWidget::InitialiseOverviewScreen()
{
	BindChangeDelegates();
	PopulateOverviewScreen();
}

void UBaseOverviewScreenWidget::BindChangeDelegates()
{
	CachedBaseManagerState->OnWorkerRosterChanged.AddUObject(this, &UBaseOverviewScreenWidget::PopulateOverviewScreen);
	CachedBaseManagerState->OnTasksChanged.AddUObject(this, &UBaseOverviewScreenWidget::PopulateOverviewScreen);
}

void UBaseOverviewScreenWidget::PopulateOverviewScreen()
{
	// --- WORKERS ---
	int32 Total = 0, Idle = 0, Working = 0, OnMission = 0, Injured = 0;
	for (UWorkerData* Worker : CachedBaseManagerState->GetAllWorkers())
	{
		if (!Worker) { continue; }
		Total++;
		switch (Worker->GetCurrentStatus())
		{
			case EWorkerStatus::EWS_Idle:      Idle++;      break;
			case EWorkerStatus::EWS_Working:   Working++;   break;
			case EWorkerStatus::EWS_OnMission: OnMission++; break;
			case EWorkerStatus::EWS_Injured:   Injured++;   break;
			default: break;
		}
	}
	WorkerDataText->SetText(FText::FromString(
		FString::Printf(TEXT("Total: %d | Idle: %d | Working: %d | On Mission: %d | Injured: %d"),
			Total, Idle, Working, OnMission, Injured)));

	// --- TASKS ---
	// TODO: Split into separate delegate bindings per task type to avoid full rebuild on every tick
	FString ResearchText;
	FString EngineeringText;
	for (const FBaseTask& Task : CachedBaseManagerState->GetActiveTasks())
	{
		const int32 SecondsRemaining = FMath::Max(0, FMath::CeilToInt(Task.BaseDuration - Task.Progress));
		const FString TaskLine = FString::Printf(TEXT("%s: %ds remaining\n"), *Task.TaskName, SecondsRemaining);

		if (Task.TaskType == ETaskType::ETT_Research)         { ResearchText    += TaskLine; }
		else if (Task.TaskType == ETaskType::ETT_Engineering) { EngineeringText += TaskLine; }
	}

	ResearchDataText->SetText(FText::FromString(
		ResearchText.IsEmpty() ? TEXT("No active research tasks") : ResearchText.TrimEnd()));
	EngineeringDataText->SetText(FText::FromString(
		EngineeringText.IsEmpty() ? TEXT("No active engineering tasks") : EngineeringText.TrimEnd()));

	// --- RESOURCES ---
	CreditDataText->SetText(FText::FromString(
		FString::Printf(TEXT("Credits: %d"), CachedBaseManagerState->GetCredits())));
	SuppliesDataText->SetText(FText::FromString(
		FString::Printf(TEXT("Supplies: %d"), CachedBaseManagerState->GetSupplies())));
}
