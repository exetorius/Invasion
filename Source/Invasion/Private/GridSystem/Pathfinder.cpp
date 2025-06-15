#include "GridSystem/Pathfinder.h"
#include "GridSystem/GridManager.h"

TArray<FIntPoint> APathfinder::FindPath(const FIntPoint Start, const FIntPoint Goal, const AGridManager* GridManager)
{
	TArray<FPathNode> OpenSet;
	TArray<FPathNode> ClosedSet;

	FPathNode StartNode;
	StartNode.GridPosition = Start;
	StartNode.GCost = 0;
	StartNode.HCost = GetHeuristic(Start, Goal);
	StartNode.Parent = nullptr;

	OpenSet.Add(StartNode);

	while (OpenSet.Num() > 0)
	{
		OpenSet.Sort([](const FPathNode& A, const FPathNode& B) { return A.FCost() < B.FCost(); });
		FPathNode CurrentNode = OpenSet[0];
		OpenSet.RemoveAt(0);
		ClosedSet.Add(CurrentNode);

		if (CurrentNode.GridPosition == Goal)
		{
			TArray<FIntPoint> Path;
			FPathNode* Node = &CurrentNode;
			while (Node)
			{
				Path.Add(Node->GridPosition);
				Node = Node->Parent;
			}
			Algo::Reverse(Path);
			return Path;
		}

		TArray<FIntPoint> Neighbours = {
			FIntPoint(CurrentNode.GridPosition.X + 1, CurrentNode.GridPosition.Y),
			FIntPoint(CurrentNode.GridPosition.X - 1, CurrentNode.GridPosition.Y),
			FIntPoint(CurrentNode.GridPosition.X, CurrentNode.GridPosition.Y + 1),
			FIntPoint(CurrentNode.GridPosition.X, CurrentNode.GridPosition.Y - 1)
		};

		for (FIntPoint NeighbourPosition : Neighbours)
		{
			if (NeighbourPosition.X < 0 || NeighbourPosition.Y < 0 || NeighbourPosition.X >= GridManager->GetGridWidth() || NeighbourPosition.Y >= GridManager->GetGridHeight())
			{
				continue;
			}

			if (ClosedSet.ContainsByPredicate([&](const FPathNode& Node) { return Node.GridPosition == NeighbourPosition; }))
			{
				continue;
			}

			float NewGCost = CurrentNode.GCost + 1;
			bool bInOpenSet = false;
			for (FPathNode& Node : OpenSet)
			{
				if (Node.GridPosition == NeighbourPosition)
				{
					if (NewGCost < Node.GCost)
					{
						Node.GCost = NewGCost;
						Node.Parent = &CurrentNode;
					}
					bInOpenSet = true;
					break;
				}
			}

			if (!bInOpenSet)
			{
				FPathNode NewNode;
				NewNode.GridPosition = NeighbourPosition;
				NewNode.GCost = NewGCost;
				NewNode.HCost = GetHeuristic(NeighbourPosition, Goal);
				NewNode.Parent = &CurrentNode;
				OpenSet.Add(NewNode);
			}
		}
	}

	return TArray<FIntPoint>();
}

float APathfinder::GetHeuristic(FIntPoint A, FIntPoint B) 
{
	return FMath::Abs(A.X - B.X) + FMath::Abs(A.Y - B.Y);
}
