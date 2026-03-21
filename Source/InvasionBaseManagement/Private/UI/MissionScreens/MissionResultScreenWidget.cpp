// CopyrightNotice


#include "UI/MissionScreens/MissionResultScreenWidget.h"

#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Core/BaseManagerState.h"

#include "Subsystems/MissionBridgeSubsystem.h"

void UMissionResultScreenWidget::CloseWidget()
{
	if (MissionBridgeSubsystem)
	{
		MissionBridgeSubsystem->ClearPendingMissionResult();
	}
	RemoveFromParent();
}

void UMissionResultScreenWidget::OnScreenDataReady()
{
	Super::OnScreenDataReady();
	
	MissionBridgeSubsystem = GetGameInstance()->GetSubsystem<UMissionBridgeSubsystem>();
	if (!MissionBridgeSubsystem) { return; }

	FMissionResult MissionResult = MissionBridgeSubsystem->GetPendingMissionResult();
	if (!MissionResult.bIsValid) { return; } 
	if (!ensure(ResultText) || !ensure(CreditsText) || !ensure(CasualtyListScrollBox)) { return; }
	
	ResultText->SetText(MissionResult.bVictory ? FText::FromString("Mission successful!") : FText::FromString("Mission failed!"));
	CreditsText->SetText(FText::AsNumber(MissionResult.CreditsAwarded));
	
	for (const FGuid& ID : MissionResult.CasualtyIDs)
	{
		UWorkerData* Soldier = CachedBaseManagerState->FindWorkerByGUID(ID);
		UE_LOG(LogTemp, Log, TEXT("MissionResultScreenWidget: FindWorkerByGUID %s — %s"), *ID.ToString(), Soldier ? *Soldier->GetWorkerName() : TEXT("NULL"));
		if (!Soldier) { continue;}
		
		UTextBlock* NameText = NewObject<UTextBlock>(this);
		NameText->SetText(FText::FromString(Soldier->GetWorkerName()));
		CasualtyListScrollBox->AddChild(NameText);
	}	
}
