// CopyrightNotice


#include "Units/PlayerUnit.h"


APlayerUnit::APlayerUnit()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetFaction(EFaction::Player);
}


