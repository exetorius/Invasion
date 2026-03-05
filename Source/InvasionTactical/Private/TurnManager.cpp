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
		StartingPhase = TurnPhase;
		PlayerUnits[CurrentUnitIndex]->OnTurnStart();		
		return;
	case 1:
		TurnPhase = ETacticalPhase::Enemy;
		StartingPhase = TurnPhase;
		EnemyUnits[CurrentUnitIndex]->OnTurnStart();
		return;
	default:
		UE_LOG(LogTemp, Warning, TEXT("ATurnManager::StartCombat - Invalid starting team"));
	}
}

void ATurnManager::RequestEndTurn()
{		
	int32 DeadUnits = 0;
	switch (TurnPhase)
	{
	case ETacticalPhase::Player:
		// Check if all enemies are dead		
		for (ABaseUnit* Unit : EnemyUnits)
		{
			if (!Unit->IsAlive()) { DeadUnits++; }
		}
		if (DeadUnits >= EnemyUnits.Num())
		{
			OnCombatEnded.Broadcast(true); // bPlayerWon
			return;
		}	
		CurrentUnitIndex++;	
		while (CurrentUnitIndex < PlayerUnits.Num() && !PlayerUnits[CurrentUnitIndex]->IsAlive()) { CurrentUnitIndex++; }
		if (CurrentUnitIndex >= PlayerUnits.Num())
		{
			TurnPhase = ETacticalPhase::Enemy; 
			if (TurnPhase == StartingPhase) { CurrentRound++; }
			CurrentUnitIndex = 0;
			EnemyUnits[CurrentUnitIndex]->OnTurnStart();
			return;
		}
		PlayerUnits[CurrentUnitIndex]->OnTurnStart();
		return;
	case ETacticalPhase::Enemy:
		// Check if all players are dead		
		for (ABaseUnit* Unit : PlayerUnits)
		{
			if (!Unit->IsAlive()) { DeadUnits++; }
		}
		if (DeadUnits >= PlayerUnits.Num())
		{
			OnCombatEnded.Broadcast(false); // bPlayerWon
			return;
		}	
		CurrentUnitIndex++;	
		while (CurrentUnitIndex < EnemyUnits.Num() && !EnemyUnits[CurrentUnitIndex]->IsAlive()) { CurrentUnitIndex++; }
		if (CurrentUnitIndex >= EnemyUnits.Num())
		{
			TurnPhase = ETacticalPhase::Player; 
			if (TurnPhase == StartingPhase) { CurrentRound++; }
			CurrentUnitIndex = 0;
			PlayerUnits[CurrentUnitIndex]->OnTurnStart();
			return;
		}
		EnemyUnits[CurrentUnitIndex]->OnTurnStart();
		return;
	case ETacticalPhase::None:
		UE_LOG(LogTemp, Warning, TEXT("ATurnManager::RequestEndTurn - Invalid turn phase"));
	}
}
