// CopyrightNotice


#include "Combat/TurnManager.h"

#include "Units/BaseUnit.h"


ATurnManager::ATurnManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATurnManager::RegisterUnit(ABaseUnit* Unit)
{
	if (!Unit) { return; }

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

void ATurnManager::StartCombat(const TArray<ABaseUnit*>& CombatUnits)
{
	for (ABaseUnit* Unit : CombatUnits)
	{
		RegisterUnit(Unit);
	}
	
	if (!ensure(PlayerUnits.Num() > 0) || !ensure(EnemyUnits.Num() > 0)) { return; }
	CurrentRound = 1;
	TurnPhase = FMath::RandBool() ? ETacticalPhase::Player : ETacticalPhase::Enemy;
	StartingPhase = TurnPhase;
	GetCurrentTeam()[CurrentUnitIndex]->OnTurnStart();
	OnActiveUnitChanged.Broadcast(GetCurrentTeam()[CurrentUnitIndex]);
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
		if (!ensure(OtherTeam.Num() > 0)) { return true; }		
		OnActiveUnitChanged.Broadcast(OtherTeam[CurrentUnitIndex]);
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
		OnCombatEnded.Broadcast(TurnPhase == ETacticalPhase::Player); // If player, we won, if enemy, we lost
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
	// TODO: Gate on caller identity — only the active unit (or PlayerController for player phase) should
	// be able to call RequestEndTurn. Enemy phase calls from player input (e.g. End Turn button) must be
	// rejected here once the persistent HUD replaces the throwaway widget.
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
	
	// Tell the next unit to start its turn
	GetCurrentTeam()[CurrentUnitIndex]->OnTurnStart();
	OnActiveUnitChanged.Broadcast(GetCurrentTeam()[CurrentUnitIndex]);
}

const TArray<ABaseUnit*>& ATurnManager::GetCurrentTeam() const
{
	return TurnPhase == ETacticalPhase::Player ? PlayerUnits : EnemyUnits;
}

const TArray<ABaseUnit*>& ATurnManager::GetOtherTeam() const
{
	return TurnPhase == ETacticalPhase::Player ? EnemyUnits : PlayerUnits;
}

ABaseUnit* ATurnManager::GetActiveUnit() const
{
	const TArray<ABaseUnit*>& CurrentTeam = GetCurrentTeam();
	if (!ensure(CurrentTeam.Num() > 0) || !ensure(CurrentUnitIndex < CurrentTeam.Num()))
	{
		return nullptr;
	} 
	return CurrentTeam[CurrentUnitIndex]; 
}
