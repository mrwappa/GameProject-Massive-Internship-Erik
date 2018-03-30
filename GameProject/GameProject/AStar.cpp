#include "stdafx.h"
#include "AStar.h"


AStar::AStar(GrowingArray<GrowingArray<AStarNode*>> aGrid)
{
	Grid = aGrid;
}


AStar::~AStar()
{
}

int AStar::GetGridRows()
{
	return Grid[0].Size();
}

int AStar::GetGridColummns()
{
	return Grid.Size();
}

bool AStar::AtEndPosition(Vector2f aEnd, GrowingArray<AStarNode*>* aClosedList)
{
	for (int i = 0; i < aClosedList->Size(); i++)
	{
		if (aClosedList->FindAtIndex(i)->GetPosition == aEnd)
		{
			return true;
		}
	}
	return false;
}

GrowingArray<AStarNode*> AStar::FindPath(Vector2f aStart, Vector2f aEnd)
{
	AStarNode* start = new AStarNode(Vector2f((int)(aStart.x / AStarNode::NodeSize), (int)(aStart.y / AStarNode::NodeSize)), true);
	AStarNode* end = new AStarNode(Vector2f((int)(aEnd.x / AStarNode::NodeSize), (int)(aEnd.y / AStarNode::NodeSize)), true);

	GrowingArray<AStarNode*> path;
	GrowingArray<AStarNode*> openList;
	GrowingArray<AStarNode*> closedList;
	GrowingArray<AStarNode*> adjancies;

	AStarNode* current = start;


	openList.Add(start);

	bool atEndPosition = AtEndPosition(aEnd,&closedList);

	while (openList.Size() != 0 and !atEndPosition)
	{
		current = openList[0];
		openList.Remove(current);
		closedList.Add(current);
		adjancies = GetAdjacentNodes(current);

		for (int i = 0; i < adjancies.Size(); i++)
		{
			
			if (closedList.Find(adjancies.FindAtIndex(i)) != -1 and adjancies.FindAtIndex(i)->GetWalkable())
			{
				AStarNode* node = adjancies[i];

				node->SetParent(current);
				node->SetTargetDistance(abs(node->GetPosition.x - aEnd.x) + abs(node->GetPosition.y - aEnd.x));
				node->SetCost(1 + node->GetParent()->GetCost());
				openList.Add(adjancies[i]);
				//sort list by F
			}

		}

		atEndPosition = AtEndPosition(aEnd, &closedList);
	}
	return GrowingArray<AStarNode*>();
}

GrowingArray<AStarNode*> AStar::GetAdjacentNodes(AStarNode * aNode)
{
	GrowingArray<AStarNode*> grArray;

	int row = (int)aNode->GetPosition().y;
	int col = (int)aNode->GetPosition().x;

	if (row + 1 < GetGridRows())
	{
		grArray.Add(Grid[col][row + 1]);
	}
	if (row - 1 >= 0)
	{
		grArray.Add(Grid[col][row - 1]);
	}
	if (col - 1 >= 0)
	{
		grArray.Add(Grid[col - 1][row]);
	}
	if (col + 1 < GetGridColummns())
	{
		grArray.Add(Grid[col + 1][row]);
	}

	return grArray;
}
