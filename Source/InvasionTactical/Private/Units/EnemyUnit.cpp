// CopyrightNotice


#include "Units/EnemyUnit.h"


AEnemyUnit::AEnemyUnit()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetFaction(EFaction::Enemy);
}

void AEnemyUnit::OnTurnStart()
{
	Super::OnTurnStart();
}


