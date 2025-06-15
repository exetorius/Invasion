#include "GridSystem/Pathfinder.h"
#include "GridSystem/GridManager.h"

TArray<FIntVector> APathfinder::FindPath(const FIntVector Start, const FIntVector Goal, const AGridManager* GridManager)
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
			TArray<FIntVector> Path;
			if (const FPathNode* Node = &CurrentNode)
			{
				Path.Add(Node->GridPosition);
				Node = Node->Parent;
			}
			Algo::Reverse(Path);
			return Path;
		}

		TArray<FIntVector> Neighbours = {
			FIntVector(CurrentNode.GridPosition.X + 1, CurrentNode.GridPosition.Y, CurrentNode.GridPosition.Z),
			FIntVector(CurrentNode.GridPosition.X - 1, CurrentNode.GridPosition.Y, CurrentNode.GridPosition.Z),
			FIntVector(CurrentNode.GridPosition.X, CurrentNode.GridPosition.Y + 1, CurrentNode.GridPosition.Z),
			FIntVector(CurrentNode.GridPosition.X, CurrentNode.GridPosition.Y - 1, CurrentNode.GridPosition.Z),
			FIntVector(CurrentNode.GridPosition.X, CurrentNode.GridPosition.Y, CurrentNode.GridPosition.Z + 1),
			FIntVector(CurrentNode.GridPosition.X, CurrentNode.GridPosition.Y, CurrentNode.GridPosition.Z - 1)
		};

		for (FIntVector NeighbourPosition : Neighbours)
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

	return TArray<FIntVector>();
}

float APathfinder::GetHeuristic(FIntVector A, FIntVector B) 
{
	return FMath::Abs(A.X - B.X) + FMath::Abs(A.Y - B.Y) + FMath::Abs(A.Z - B.Z);
}
