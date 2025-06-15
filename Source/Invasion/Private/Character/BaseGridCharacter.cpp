// CopyrightNotice


#include "Character/BaseGridCharacter.h"

#include "GridSystem/GridManager.h"
#include "GridSystem/Pathfinder.h"

ABaseGridCharacter::ABaseGridCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	createde
}

void ABaseGridCharacter::MoveToGridCell(FIntPoint TargetCell) const
{
	AGridManager* GridManager = Cast<AGridManager>(GetWorld()->GetFirstPlayerController()->GetPawn());
	APathfinder* Pathfinder = GetWorld()->SpawnActor<APathfinder>();

	FIntPoint StartCell = GridManager->GetClosestGridIndex(GetActorLocation());
	TArray<FIntPoint> Path = Pathfinder->FindPath(StartCell, TargetCell, GridManager);

	if (Path.Num() > 0)
	{
		for (FIntPoint Cell : Path)
		{
			FVector TargetLocation = GridManager->GetCellWorldLocation(Cell.X, Cell.Y);
			GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(TargetLocation);
		}
	}

	Pathfinder->Destroy();
}

void ABaseGridCharacter::StartTurn()
{
}



