// CopyrightNotice


#include "Pathfinder.h"

#include "Grid/TacticalGrid.h"
#include "Grid/TacticalGridTile.h"

TArray<ATacticalGridTile*> UPathfinder::FindPath(ATacticalGridTile* StartTile, const ATacticalGridTile* EndTile) const
{	
	TArray<FPathNode> AllNodes;
	TArray<int32> OpenList;
	TArray<ATacticalGridTile*> ClosedList;
	
	FPathNode StartNode;
	StartNode.Tile = StartTile;
	StartNode.GCost = 0;
	StartNode.HCost =
		(FMath::Abs(StartTile->GetGridCoordinates().X - EndTile->GetGridCoordinates().X) + 
		FMath::Abs(StartTile->GetGridCoordinates().Y - EndTile->GetGridCoordinates().Y)) * 10;
	StartNode.Parent = -1;
	
	AllNodes.Add(StartNode);
	OpenList.Add(AllNodes.Num() - 1);	
	int32 CurrentIndex = 0;
	
	// Pathfind from start to end
	while (OpenList.Num() > 0)
	{		
		CurrentIndex = OpenList[0];
		for (const int32 NodeIndex : OpenList)
		{
			if (AllNodes[NodeIndex].GetFCost() < AllNodes[CurrentIndex].GetFCost())
			{
				CurrentIndex = NodeIndex;
			}
		}
		OpenList.Remove(CurrentIndex);
		ClosedList.Add(AllNodes[CurrentIndex].Tile);
		
		// Destination check - have we reached our end point
		if (AllNodes[CurrentIndex].Tile == EndTile) { break; }
		
		// Neighbour check & node creation		
		for (ATacticalGridTile* NeighbourTile : TacticalGrid->GetNeighbours(AllNodes[CurrentIndex].Tile->GetGridCoordinates()))
		{
			if (ClosedList.Contains(NeighbourTile) || !NeighbourTile->IsWalkable()) { continue;}
			
			// Create the neighbour node
			FPathNode CurrentNeighbour;
			CurrentNeighbour.Tile = NeighbourTile;
			CurrentNeighbour.GCost = AllNodes[CurrentIndex].GCost + 10;
			CurrentNeighbour.HCost = 
				(FMath::Abs(NeighbourTile->GetGridCoordinates().X - EndTile->GetGridCoordinates().X) + 
				FMath::Abs(NeighbourTile->GetGridCoordinates().Y - EndTile->GetGridCoordinates().Y)) * 10;
			CurrentNeighbour.Parent = CurrentIndex;			
			
			// Check if NeighbourTile already exists inside AllNodes
			FPathNode* ExistingNode = AllNodes.FindByPredicate([NeighbourTile](const FPathNode& Node)
			{
				return Node.Tile == NeighbourTile;
			});
			
			// Add to AllNodes if we haven't yet seen the node, and if we have, is it a better candidate?
			if (ExistingNode == nullptr)
			{
				AllNodes.Add(CurrentNeighbour); 
				OpenList.Add(AllNodes.Num() - 1);
			}
			else
			{
				if (CurrentNeighbour.GCost < ExistingNode->GCost)
				{
					*ExistingNode = CurrentNeighbour;
				}
			}
		}		
	}	
	
	// Reverse path trace
	TArray<ATacticalGridTile*> Path;
	
	// No valid path was found, return an empty array
	if (AllNodes[CurrentIndex].Tile != EndTile) { return Path; }
	
	// StartNode parent is -1
	while (CurrentIndex != -1)
	{		
		// Not reached the start yet, add the tile and get the next parent node
		FPathNode Node = AllNodes[CurrentIndex];
		Path.Add(Node.Tile);
		CurrentIndex = Node.Parent;
	}
	Algo::Reverse(Path);
	
	return Path;
}
