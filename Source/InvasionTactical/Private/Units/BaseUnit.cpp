// CopyrightNotice


#include "Units/BaseUnit.h"

#include "Grid/TacticalGridTile.h"


ABaseUnit::ABaseUnit()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseUnit::SetFaction(const EFaction NewFaction)
{
	if (Faction == EFaction::None)
	{
		Faction = NewFaction;
	}
	// TODO: Mind control / faction swap mechanic will need to override this blocker
}

void ABaseUnit::SetCurrentTile(ATacticalGridTile* NewTile)
{
	if (!ensure(NewTile)) { return; }
	
	// Clear the current tile's occupier
	if (CurrentTile && CurrentTile != NewTile)
	{
		CurrentTile->SetOccupyingUnit(nullptr);
	}
	CurrentTile = NewTile;
	NewTile->SetOccupyingUnit(this);
}

void ABaseUnit::Kill()
{
	if (CombatState != ECombatState::Dead)
	{
		if (CurrentTile)
		{
			CurrentTile->SetOccupyingUnit(nullptr);
		}
		Health = 0;
		MovementPointsRemaining = 0;
		CombatState = ECombatState::Dead;
	}
}

void ABaseUnit::AddHealth(float HealthToAdd)
{
	if (IsAlive())
	{
		Health = FMath::Clamp(Health + HealthToAdd, 0.f, MaxHealth);
	}
}

void ABaseUnit::RemoveHealth(float HealthToRemove)
{
	if (IsAlive())
	{
		Health = FMath::Max(Health - HealthToRemove, 0.f);
		if (Health <= 0.f)
		{
			Kill();
		}
	}
}

void ABaseUnit::OnTurnStart()
{
	MovementPointsRemaining = MaxMovementPoints;
}


