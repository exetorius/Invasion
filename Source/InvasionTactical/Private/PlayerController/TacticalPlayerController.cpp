// CopyrightNotice


#include "PlayerController/TacticalPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Combat/TurnManager.h"
#include "Grid/TacticalGrid.h"
#include "Grid/TacticalGridTile.h"
#include "Kismet/GameplayStatics.h"
#include "Units/BaseUnit.h"
#include "Units/PlayerUnit.h"

void ATacticalPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Otherwise we get no cursor on screen
	bShowMouseCursor = true;
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Tactical, 0);
	}
	
	TacticalGrid = Cast<ATacticalGrid>(UGameplayStatics::GetActorOfClass(GetWorld(), ATacticalGrid::StaticClass()));
	TurnManager = Cast<ATurnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATurnManager::StaticClass()));
	
	if (!ensure(TacticalGrid) || !ensure(TurnManager)) { return; }
	
	TurnManager->OnActiveUnitChanged.AddDynamic(this, &ATacticalPlayerController::OnActiveUnitChanged);
	ABaseUnit* CurrentUnit = TurnManager->GetActiveUnit();
	if (CurrentUnit && CurrentUnit->GetFaction() == EFaction::Player)
	{
		ActiveUnit = CurrentUnit;
	}

}

void ATacticalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent);

	EIC->BindAction(IA_Select, ETriggerEvent::Started, this, &ATacticalPlayerController::OnSelectClicked);

}

void ATacticalPlayerController::OnActiveUnitChanged(ABaseUnit* NewActiveUnit)
{
	if (!NewActiveUnit || NewActiveUnit->GetFaction() != EFaction::Player)
	{
		// Clear the active unit if not valid or its enemy / civilian turn
		ActiveUnit = nullptr;
		return;
	}
	
	ActiveUnit = NewActiveUnit;
}

void ATacticalPlayerController::OnSelectClicked()
{
	if (!ActiveUnit) { return; }

	// Line trace to find the hit tile
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_GameTraceChannel3, false, Hit);
	if (ATacticalGridTile* HitTile = Cast<ATacticalGridTile>(Hit.GetActor()))
	{
		if (HitTile->IsHighlighted())
		{
			RequestMoveToTile(HitTile);
		}
	}
}

void ATacticalPlayerController::RequestMoveToTile(ATacticalGridTile* MoveTile)
{
	// TODO: Server RPC boundary — becomes Server RPC when networking lands
	if (!MoveTile || !ActiveUnit || !TacticalGrid) { return; }
	APlayerUnit* PlayerUnit = Cast<APlayerUnit>(ActiveUnit);
	if (!ensure(PlayerUnit)) { return; }
	PlayerUnit->MoveToTile(MoveTile);
	TacticalGrid->ClearHighlights();
}
