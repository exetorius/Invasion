// CopyrightNotice

#include "UI/ManagementScreens/BaseOverviewScreenWidget.h"

#include "Components/ComboBoxString.h"
#include "Core/BaseManagerState.h"
#include "Data/WorkerData.h"
#include "Components/TextBlock.h"
#include "Controller/ManagementPlayerController.h"

void UBaseOverviewScreenWidget::OnScreenDataReady()
{
	InitialiseOverviewScreen();
}

void UBaseOverviewScreenWidget::InitialiseOverviewScreen()
{
	BindChangeDelegates();
	PopulateOverviewScreen();
	
	//TODO Move out when we move nation select to another screen
	PopulateNationComboBox();
}

void UBaseOverviewScreenWidget::BindChangeDelegates()
{
	CachedBaseManagerState->OnWorkerRosterChanged.AddUObject(this, &UBaseOverviewScreenWidget::PopulateOverviewScreen);
	CachedBaseManagerState->OnTasksChanged.AddUObject(this, &UBaseOverviewScreenWidget::PopulateOverviewScreen);
}

void UBaseOverviewScreenWidget::OnNationSelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// Ignore programmatic selections (from SetSelectedOption above)
	if (SelectionType == ESelectInfo::Direct) { return; }

	ENation SelectedNation = StringToNation(SelectedItem);
	if (SelectedNation == ENation::EN_None) { return; }

	CachedPlayerController->Server_RequestSetNation(SelectedNation);
	PlayerNationComboBox->SetIsEnabled(false);
}

void UBaseOverviewScreenWidget::PopulateNationComboBox()
{
	if (!ensure(PlayerNationComboBox)) { return; }

	PlayerNationComboBox->AddOption("United Kingdom");
	PlayerNationComboBox->AddOption("United States");
	PlayerNationComboBox->AddOption("Australia");
	PlayerNationComboBox->AddOption("China");
	PlayerNationComboBox->AddOption("France");

	// Bind the selection callback
	PlayerNationComboBox->OnSelectionChanged.AddDynamic(this, &UBaseOverviewScreenWidget::OnNationSelected);

	// If nation already set (reconnect case), pre-select and lock
	ENation CurrentNation = CachedBaseManagerState->GetPlayerNation();
	if (CurrentNation != ENation::EN_None)
	{
		PlayerNationComboBox->SetSelectedOption(NationToString(CurrentNation));
		PlayerNationComboBox->SetIsEnabled(false);
	}
}

//TODO Move these to nation select screen
ENation UBaseOverviewScreenWidget::StringToNation(FString String)
{
	if (String == "United Kingdom") return ENation::EN_UK;
	if (String == "United States")  return ENation::EN_US;
	if (String == "Australia")      return ENation::EN_AUS;
	if (String == "China")          return ENation::EN_CHN;
	if (String == "France")         return ENation::EN_FRA;
	return ENation::EN_None;
}

FString UBaseOverviewScreenWidget::NationToString(ENation Nation)
{
	switch (Nation)
	{
		case ENation::EN_UK: return "United Kingdom";
		case ENation::EN_US: return "United States";
		case ENation::EN_AUS: return "Australia";
		case ENation::EN_CHN: return "China";
		case ENation::EN_FRA: return "France";
		default: return "None";
	}
}
//TODO END 

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
