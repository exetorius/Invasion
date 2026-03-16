// CopyrightNotice


#include "GameMode/TacticalGameMode.h"

#include "Combat/CombatManager.h"
#include "Combat/TurnManager.h"
#include "Grid/TacticalGrid.h"
#include "Kismet/GameplayStatics.h"
#include "Units/BaseUnit.h"
#include "Units/EnemyUnit.h"
#include "Units/PlayerUnit.h"


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
		UE_LOG(LogTemp, Warning, TEXT("TacticalGameMode::BeginPlay — ExpectedUnitCount = %d"), ExpectedUnitCount);
	}
}

void ATacticalGameMode::RegisterUnit(ABaseUnit* Unit)
{
	if (!Unit) { return; }

	Units.Add(Unit);
	UE_LOG(LogTemp, Warning, TEXT("TacticalGameMode::RegisterUnit — %s registered (%d / %d)"), *Unit->GetName(), Units.Num(), ExpectedUnitCount);

	if (AEnemyUnit* EnemyUnit = Cast<AEnemyUnit>(Unit))
	{
		EnemyUnit->Initialise(TurnManager, CombatManager, TacticalGrid);
	}

	if (APlayerUnit* PlayerUnit = Cast<APlayerUnit>(Unit))
	{
		PlayerUnit->Initialise(TacticalGrid);
	}

	if (Units.Num() == ExpectedUnitCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("TacticalGameMode::RegisterUnit — all units registered, calling StartCombat"));
		TurnManager->StartCombat(Units);
	}
}
