// CopyrightNotice


#include "Grid/TacticalGridTile.h"


ATacticalGridTile::ATacticalGridTile()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATacticalGridTile::BeginPlay()
{
	Super::BeginPlay();
	
	if (const UWorld* World = GetWorld())
	{
		bIsWalkable = !World->OverlapAnyTestByChannel(
			GetActorLocation(), 
			FQuat::Identity, 
			ECC_GameTraceChannel1, 
			FCollisionShape::MakeBox(FVector(BoxHalfExtents)),
			FCollisionQueryParams::DefaultQueryParam				
			);
	}
}

