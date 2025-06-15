// CopyrightNotice


#include "Character/BaseGridCharacter.h"

#include "GameMode/InvasionBattleGameMode.h"
#include "GridSystem/GridManager.h"
#include "GridSystem/Pathfinder.h"
#include "Kismet/GameplayStatics.h"

ABaseGridCharacter::ABaseGridCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseGridCharacter::MoveToGridCell(FIntVector TargetCell) const
{
	if (const AInvasionBattleGameMode* GameMode = Cast<AInvasionBattleGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (APathfinder* Pathfinder = GetWorld()->SpawnActor<APathfinder>())
		{
			UE_LOG(LogTemp, Warning, TEXT("ABaseGridCharacter::MoveToGridCell: %d, %d"), TargetCell.X, TargetCell.Y);
			
			const FIntVector StartCell = GameMode->GridManager->GetClosestGridIndex(GetActorLocation());
			TArray<FIntVector> Path = Pathfinder->FindPath(StartCell, TargetCell, GameMode->GridManager);

			if (Path.Num() > 0)
			{
				for (const FIntVector Cell : Path)
				{
					FVector TargetLocation = GameMode->GridManager->GetCellWorldLocation(Cell.X, Cell.Y, Cell.Z);
					GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(TargetLocation);
				}
			}

			Pathfinder->Destroy();
		}
	}
}

void ABaseGridCharacter::StartTurn()
{
}



