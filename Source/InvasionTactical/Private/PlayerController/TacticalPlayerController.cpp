// CopyrightNotice


#include "PlayerController/TacticalPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Combat/CombatManager.h"
#include "Combat/TurnManager.h"
#include "Grid/CoverActor.h"
#include "Grid/TacticalGrid.h"
#include "Grid/TacticalGridTile.h"
#include "Kismet/GameplayStatics.h"
#include "Units/BaseUnit.h"
#include "Units/PlayerUnit.h"

void ATacticalPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TacticalGrid = Cast<ATacticalGrid>(UGameplayStatics::GetActorOfClass(GetWorld(), ATacticalGrid::StaticClass()));
	TurnManager = Cast<ATurnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ATurnManager::StaticClass()));
	CombatManager = Cast<ACombatManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACombatManager::StaticClass()));
	
	if (!ensure(TacticalGrid) || !ensure(TurnManager) || !ensure(CombatManager)) { return; }
	
	TurnManager->OnActiveUnitChanged.AddDynamic(this, &ATacticalPlayerController::OnActiveUnitChanged);
	ABaseUnit* CurrentUnit = TurnManager->GetActiveUnit();
	if (CurrentUnit && CurrentUnit->GetFaction() == EFaction::Player)
	{
		ActiveUnit = CurrentUnit;
	}
}

void ATacticalPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_Tactical, 0);
	}
}

void ATacticalPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent);

	EIC->BindAction(IA_Select, ETriggerEvent::Started, this, &ATacticalPlayerController::OnSelectClicked);
	EIC->BindAction(IA_Attack, ETriggerEvent::Started, this, &ATacticalPlayerController::OnAttackClicked);
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

void ATacticalPlayerController::OnAttackClicked()
{
	if (!ActiveUnit) { return; }

	// Line trace to find the hit unit
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_GameTraceChannel4, false, Hit);
	if (ABaseUnit* HitUnit = Cast<ABaseUnit>(Hit.GetActor()))
	{
		if (HitUnit->IsAlive() && HitUnit->GetFaction() != EFaction::Player)
		{
			RequestAttackUnit(HitUnit);
		}
	}
}

void ATacticalPlayerController::RequestAttackUnit(ABaseUnit* TargetUnit)
{	
	// TODO: Server RPC boundary — becomes Server RPC when networking lands
	if (!TargetUnit || !ActiveUnit || !CombatManager || !TacticalGrid) { return; }
	if (ActiveUnit->HasAttackedThisTurn()) { return; }
	
	const FIntPoint AttackerCoordinates = ActiveUnit->GetCurrentTile()->GetGridCoordinates();
	const FIntPoint DefenderCoordinates = TargetUnit->GetCurrentTile()->GetGridCoordinates();

	const int32 ManhattanDist = FMath::Abs(AttackerCoordinates.X - DefenderCoordinates.X) + FMath::Abs(AttackerCoordinates.Y - DefenderCoordinates.Y);

	// Skip if out of shooting range
	if (ManhattanDist > ActiveUnit->GetMaxShootRange()) { return; }

	// Skip if obstructed by a wall
	FHitResult WallHit;
	if (GetWorld()->LineTraceSingleByChannel(WallHit, ActiveUnit->GetActorLocation(), TargetUnit->GetActorLocation(), ECC_GameTraceChannel1)) { return; }

	// Skip if behind full cover
	FHitResult CoverHit;
	if (GetWorld()->LineTraceSingleByChannel(CoverHit, ActiveUnit->GetActorLocation(), TargetUnit->GetActorLocation(), ECC_GameTraceChannel2))
	{
		const ACoverActor* Cover = Cast<ACoverActor>(CoverHit.GetActor());
		if (Cover && Cover->GetCoverType() == ECoverType::Full) { return; }
	}

	// TODO: Replace GEngine messages with world-space floating text popup above target unit (#46)
	const FCombatHitResult HitResult = CombatManager->ResolveHit(ActiveUnit, TargetUnit, TacticalGrid->GetCover(DefenderCoordinates, AttackerCoordinates), false);
	if (HitResult.bHit)
	{
		const FString Message = HitResult.bCrit
			? FString::Printf(TEXT("CRIT! -%.0f"), HitResult.DamageDealt)
			: FString::Printf(TEXT("HIT -%.0f"), HitResult.DamageDealt);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, Message);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT("MISS"));
	}
	ActiveUnit->ConsumeMovementPoints(ActiveUnit->GetMovementPointsRemaining() / 2);
	ActiveUnit->ConsumeAttack();
}
