// CopyrightNotice


#include "TacticalGrid.h"


// Sets default values
ATacticalGrid::ATacticalGrid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATacticalGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATacticalGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

