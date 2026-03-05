// CopyrightNotice


#include "TurnManager.h"

#include "Units/BaseUnit.h"


ATurnManager::ATurnManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATurnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurnManager::RegisterUnit(ABaseUnit* Unit)
{
	if (!ensure(Unit)) { return; }

	switch (Unit->GetFaction())
	{
		case EFaction::Player:
		case EFaction::CivilianFriendly:
			PlayerUnits.Add(Unit);
			return;
		case EFaction::Enemy:
		case EFaction::CivilianHostile:
			EnemyUnits.Add(Unit);
			return;
		case EFaction::None:
			return;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Unknown faction for unit: %s"), *Unit->GetName());
	}
}

void ATurnManager::StartCombat()
{
	if (!ensure(PlayerUnits.Num() > 0) || !ensure(EnemyUnits.Num() > 0)) { return; }
	CurrentRound = 1;
	switch (FMath::RandRange(0, 1))
	{
	case 0:
		TurnPhase = ETacticalPhase::Player;			
		break;
	case 1:
		TurnPhase = ETacticalPhase::Enemy;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("ATurnManager::StartCombat - Invalid starting team"));
		return;
	}
	StartingPhase = TurnPhase;
	GetCurrentTeam()[CurrentUnitIndex]->OnTurnStart();	
}

bool ATurnManager::ShouldStartNextPhase()
{
	const TArray<ABaseUnit*>& CurrentTeam = GetCurrentTeam();
	const TArray<ABaseUnit*>& OtherTeam = GetOtherTeam();
	if (CurrentUnitIndex >= CurrentTeam.Num())
	{
		TurnPhase = TurnPhase == ETacticalPhase::Player ? ETacticalPhase::Enemy : ETacticalPhase::Player; 
		if (TurnPhase == StartingPhase) { CurrentRound++; }
		CurrentUnitIndex = 0;
		OtherTeam[CurrentUnitIndex]->OnTurnStart();
		return true;
	}
	return false;
}

bool ATurnManager::HasCombatEnded() const
{
	int32 DeadUnits = 0;
	const TArray<ABaseUnit*>& OtherTeam = GetOtherTeam();
	for (ABaseUnit* Unit : OtherTeam)
	{
		if (!Unit->IsAlive()) { DeadUnits++; }
	}
	if (DeadUnits >= OtherTeam.Num())
	{
		OnCombatEnded.Broadcast(TurnPhase == ETacticalPhase::Player); // bPlayerWon
		return true;
	}	
	return false;
}

void ATurnManager::AdvanceToNextLiveUnit()
{
	const TArray<ABaseUnit*>& CurrentTeam = GetCurrentTeam();
	CurrentUnitIndex++;	
	while (CurrentUnitIndex < CurrentTeam.Num() && !CurrentTeam[CurrentUnitIndex]->IsAlive()) { CurrentUnitIndex++; }
}

void ATurnManager::RequestEndTurn()
{			
	if (TurnPhase == ETacticalPhase::None)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATurnManager::RequestEndTurn - Cannot end turn when no combat is active"));
		return;
	}

	// Check if all enemies are dead		
	if (HasCombatEnded()) { return; }
	
	// Skip over dead units
	AdvanceToNextLiveUnit();
	
	// If no remaining units, switch teams
	if (ShouldStartNextPhase()) { return; }
	
	// Tell next unit to start its turn
	GetCurrentTeam()[CurrentUnitIndex]->OnTurnStart();
}

const TArray<ABaseUnit*>& ATurnManager::GetCurrentTeam() const
{
	return TurnPhase == ETacticalPhase::Player ? PlayerUnits : EnemyUnits;
}

const TArray<ABaseUnit*>& ATurnManager::GetOtherTeam() const
{
	return TurnPhase == ETacticalPhase::Player ? EnemyUnits : PlayerUnits;
}