// CopyrightNotice


#include "UI/MissionScreens/MissionSelectScreenWidget.h"

#include "Components/ScrollBox.h"
#include "Core/BaseManagerState.h"
#include "Data/MissionData.h"
#include "Data/WorkerData.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/MissionBridgeSubsystem.h"
#include "UI/Tiles/RosterWorkerTileWidget.h"

void UMissionSelectScreenWidget::Launch()
{
	if (SelectedSoldiers.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UMissionSelectScreenWidget::Launch - No soldiers selected"));
		return;
	}
	
	if (!ensure(!TacticalLevel.IsNull())) { return; }
	
	TArray<FMissionSoldier> SelectedSoldierData;
	for (const UWorkerData* Worker : SelectedSoldiers)
	{
		FMissionSoldier SoldierData;
		SoldierData.WorkerID = Worker->GetWorkerUniqueID();
		SoldierData.DisplayName = FText::FromString(Worker->GetWorkerName());
		
		SelectedSoldierData.Add(SoldierData);
	}
	
	if (UMissionBridgeSubsystem* MissionBridgeSubsystem = GetGameInstance()->GetSubsystem<UMissionBridgeSubsystem>())
	{
		MissionBridgeSubsystem->SetPendingSquad(SelectedSoldierData);
	}	
	
	//Change level or request server to change level so clients follow - currently only clients who want to join the mission should be yoinked
	UGameplayStatics::OpenLevel(GetWorld(), FName(TacticalLevel.GetAssetName()));
}

void UMissionSelectScreenWidget::SelectSoldier(UWorkerData* SelectedSoldier)
{
	if (SelectedSoldier && !SelectedSoldiers.Contains(SelectedSoldier) && SelectedSoldiers.Num() < MaxSquadSize)
	{
		SelectedSoldiers.Add(SelectedSoldier);
		AvailableSoldiers.Remove(SelectedSoldier);
		
		PopulateAvailableSoldiersList();
		PopulateSelectedSoldiersList();
	}
}

void UMissionSelectScreenWidget::DeselectSoldier(UWorkerData* DeselectedSoldier)
{
	if (DeselectedSoldier && SelectedSoldiers.Contains(DeselectedSoldier))
	{
		SelectedSoldiers.Remove(DeselectedSoldier);
		AvailableSoldiers.Add(DeselectedSoldier);
		
		PopulateAvailableSoldiersList();
		PopulateSelectedSoldiersList();
	}
}

void UMissionSelectScreenWidget::OnScreenDataReady()
{
	PopulateWorkerList();		
	CachedBaseManagerState->OnWorkerRosterChanged.AddUObject(this, &UMissionSelectScreenWidget::OnWorkerRosterUpdated);
}

void UMissionSelectScreenWidget::PopulateWorkerList()
{
	if (!ensure(CachedBaseManagerState)) { return; }
	
	const TArray<TObjectPtr<UWorkerData>>& AllWorkers = CachedBaseManagerState->GetAllWorkers();
	
	UE_LOG(LogTemp, Log, TEXT("MissionSelectScreenWidget: Populating %d workers"), AllWorkers.Num());
	
	AvailableSoldiers.Empty();
	
	for (UWorkerData* Worker : AllWorkers)
	{
		if (Worker->GetRole() == EWorkerRole::Soldier && Worker->GetCurrentStatus() != EWorkerStatus::OnMission && !SelectedSoldiers.Contains(Worker))
		{
			AvailableSoldiers.Add(Worker);
		}
	}
	
	PopulateAvailableSoldiersList();
	PopulateSelectedSoldiersList();
}

void UMissionSelectScreenWidget::PopulateAvailableSoldiersList()
{
	if (!ensure(AvailableSoldiersScrollBox))	{ return; }
	
	UE_LOG(LogTemp, Log, TEXT("MissionSelectScreenWidget: Populating worker list"));
	
	AvailableSoldiersScrollBox->ClearChildren();	

	for (UWorkerData* Soldier : AvailableSoldiers)
	{
		if (Soldier && WorkerTileWidget)
		{
			if (URosterWorkerTileWidget* Tile = CreateWidget<URosterWorkerTileWidget>(this, WorkerTileWidget))
			{
				Tile->SetWorkerData(Soldier);					
				Tile->SetActionLabel(FText::FromString("Select"));
				Tile->OnActionClicked.BindUObject(this, &UMissionSelectScreenWidget::SelectSoldier);
				AvailableSoldiersScrollBox->AddChild(Tile);
			}
		}
	}
}

void UMissionSelectScreenWidget::PopulateSelectedSoldiersList()
{
	if (!ensure(SelectedSoldiersScrollBox))	{ return; }
	
	UE_LOG(LogTemp, Log, TEXT("MissionSelectScreenWidget: Populating worker list"));
	
	SelectedSoldiersScrollBox->ClearChildren();	

	for (UWorkerData* Soldier : SelectedSoldiers)
	{
		if (Soldier && WorkerTileWidget)
		{
			if (URosterWorkerTileWidget* Tile = CreateWidget<URosterWorkerTileWidget>(this, WorkerTileWidget))
			{
				Tile->SetWorkerData(Soldier);					
				Tile->SetActionLabel(FText::FromString("De-Select"));
				Tile->OnActionClicked.BindUObject(this, &UMissionSelectScreenWidget::DeselectSoldier);
				SelectedSoldiersScrollBox->AddChild(Tile);
			}
		}
	}
}

void UMissionSelectScreenWidget::OnWorkerRosterUpdated()
{
	PopulateWorkerList();	
}
