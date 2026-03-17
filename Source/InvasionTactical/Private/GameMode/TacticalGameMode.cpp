// CopyrightNotice


#include "GameMode/TacticalGameMode.h"

#include "Combat/CombatManager.h"
#include "Combat/TurnManager.h"
#include "Grid/TacticalGrid.h"
#include "Kismet/GameplayStatics.h"
#include "Units/BaseUnit.h"
#include "Units/EnemyUnit.h"
#include "Units/PlayerUnit.h"
#include "Data/MissionSoldier.h"


void ATacticalGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (const UWorld* World = GetWorld())
	{
		TacticalGrid = Cast<ATacticalGrid>(UGameplayStatics::GetActorOfClass(World, ATacticalGrid::StaticClass()));
		TurnManager = Cast<ATurnManager>(UGameplayStatics::GetActorOfClass(World, ATurnManager::StaticClass()));
		CombatManager = Cast<ACombatManager>(UGameplayStatics::GetActorOfClass(World, ACombatManager::StaticClass()));
		TArray<AActor*> DiscoveredUnits;
		UGameplayStatics::GetAllActorsOfClass(World, ABaseUnit::StaticClass(), DiscoveredUnits);
		ExpectedUnitCount = DiscoveredUnits.Num();
		for (ABaseUnit* Unit : Units)
		{
			if (AEnemyUnit* Enemy = Cast<AEnemyUnit>(Unit)) { Enemy->Initialise(TurnManager, CombatManager, TacticalGrid); }
			if (APlayerUnit* Player = Cast<APlayerUnit>(Unit)) { Player->Initialise(TacticalGrid, FMissionSoldier()); } // TODO: Pass in actual FMissionSoldier data (#52)
		}
		TryStartCombat();
	}
}

void ATacticalGameMode::TryStartCombat()
{
	if (ExpectedUnitCount <= 0 || Units.Num() != ExpectedUnitCount) { return; }
	if (!ensure(TurnManager)) { return; }
	TurnManager->StartCombat(Units);
}

void ATacticalGameMode::RegisterUnit(ABaseUnit* Unit)
{
	if (!Unit) { return; }

	Units.Add(Unit);
	if (AEnemyUnit* EnemyUnit = Cast<AEnemyUnit>(Unit))
	{
		EnemyUnit->Initialise(TurnManager, CombatManager, TacticalGrid);
	}

	if (APlayerUnit* PlayerUnit = Cast<APlayerUnit>(Unit))
	{
		// TODO: Pass in actual FMissionSoldier data (#52)
		PlayerUnit->Initialise(TacticalGrid, FMissionSoldier());
	}

	TryStartCombat();
}
