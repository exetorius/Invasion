// CopyrightNotice


#include "Pathfinder.h"

#include "Grid/TacticalGrid.h"
#include "Grid/TacticalGridTile.h"

TArray<ATacticalGridTile*> UPathfinder::FindPath(ATacticalGridTile* StartTile, ATacticalGridTile* EndTile)
{	
	TArray<FPathNode> AllNodes;
	TArray<int32> OpenList;
	TArray<ATacticalGridTile*> ClosedList;
	
	FPathNode StartNode;
	StartNode.Tile = StartTile;
	StartNode.GCost = 0;
	StartNode.HCost = 0;
	StartNode.Parent = -1;
	AllNodes.Add(StartNode);	
	OpenList.Add(AllNodes.Num() - 1);
	
	while (OpenList.Num() > 0)
	{
		FPathNode CurrentTile = AllNodes[OpenList[0]];
		
		for (int32 NodeIndex : OpenList)
		{			
			FPathNode Node = AllNodes[NodeIndex];
			if (Node.GetFCost() < CurrentTile.GetFCost())
			{
				CurrentTile = Node;					
			}			
		}
		//OpenList.Remove(CurrentTile);
		//ClosedList.Add(CurrentTile.Tile);
		
		
		for (ATacticalGridTile* NeighbourTile : TacticalGrid->GetNeighbours(CurrentTile.Tile->GetGridCoordinates()))
		{
			if (ClosedList.Contains(NeighbourTile) || !NeighbourTile->IsWalkable() || NeighbourTile->IsOccupied()) { continue;}
			
			FPathNode CurrentNeighbour;
			CurrentNeighbour.Tile = NeighbourTile;
			CurrentNeighbour.GCost = CurrentTile.GCost + 10;
			CurrentNeighbour.HCost = NeighbourTile->GetDistanceTo(EndTile);
			CurrentNeighbour.Parent = CurrentTile.Parent;			
			
			if (CurrentNeighbour.GCost < CurrentTile.GCost)
			{
				CurrentTile = CurrentNeighbour;
			}
			//OpenList.Add(CurrentNeighbour);	
		}
		
	}	
}
