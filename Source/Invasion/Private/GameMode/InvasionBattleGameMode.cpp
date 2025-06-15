// CopyrightNotice


#include "GameMode/InvasionBattleGameMode.h"

#include "GridSystem/GridManager.h"
#include "Kismet/GameplayStatics.h"

void AInvasionBattleGameMode::BeginPlay()
{
	Super::BeginPlay();

	GridManager = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(this, AGridManager::StaticClass()));

	if (GridManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("AInvasionBattleGameMode::BeginPlay: GridManager is alive"));
	}
}
