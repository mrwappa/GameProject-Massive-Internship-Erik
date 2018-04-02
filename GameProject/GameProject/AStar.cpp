#include "stdafx.h"
#include "AStar.h"


AStar::AStar(float aRows, float aColumns)
{

	for (int i = 0; i < aRows; i++)
	{
		Grid.Add(new GrowingArray<AStarNode*>);
		for (int j = 0; j < aColumns; j++)
		{
			Grid[i]->Add(new AStarNode(Vector2f(i, j), true));
		}
	}
}


AStar::~AStar()
{

}

void AStar::DestroyGrid()
{
	for (int i = 0; i < Grid.Size(); i++)
	{
		Grid[i]->DeleteAll();
	}
	for (int i = 0; i < Grid.Size(); i++)
	{
		delete Grid[i];
	}
}

GrowingArray<AStarNode*> AStar::FindPath(Vector2f aStart, Vector2f aEnd)
{
	AStarNode* start = Grid.FindAtIndex((int)(aStart.x / AStarNode::NodeSize))->FindAtIndex((int)(aStart.y / AStarNode::NodeSize));
	AStarNode* end = Grid.FindAtIndex((int)(aEnd.x / AStarNode::NodeSize))->FindAtIndex((int)(aEnd.y / AStarNode::NodeSize));

	if (!end->GetWalkable())
	{
		return NULL;
	}

	GrowingArray<AStarNode*> path;
	GrowingArray<AStarNode*> openList;
	GrowingArray<AStarNode*> closedList;
	GrowingArray<AStarNode*> adjencies;

	AStarNode* current = start;

	openList.Add(start);

	while (openList.Size() != 0 and !AtEndPosition(end->GetPosition(), &closedList))
	{
		current = openList[0];
		openList.Remove(current);
		closedList.Add(current);
		adjencies = GetAdjacentNodes(current);

		for (int i = 0; i < adjencies.Size(); i++)
		{
			AStarNode* node = adjencies[i];
			if (closedList.Find(node) == -1 and node->GetWalkable())
			{
				if (openList.Find(node) == -1)
				{
					node->SetParent(current);
					node->SetTargetDistance(abs(node->GetPosition().x - end->GetPosition().x) + abs(node->GetPosition().y - end->GetPosition().y));
					node->SetCost(1 + node->GetParent()->GetCost());
					openList.Add(node);
					SortByF(&openList);
				}
				
			}
		}
	}

	if (!AtEndPosition(end->GetPosition(), &closedList))
	{
		return NULL;
	}

	AStarNode* node = closedList[closedList.Find(current)];
	while (node->GetParent() != start and node != NULL)
	{
		path.Add(node);
		node = node->GetParent();
	}

	return path;
}

GrowingArray<AStarNode*> AStar::GetAdjacentNodes(AStarNode* aNode)
{
	GrowingArray<AStarNode*> nodes;

	int row = (int)aNode->GetPosition().y;
	int col = (int)aNode->GetPosition().x;
	
	if (row + 1 < GetRows())
	{
		nodes.Add(Grid.FindAtIndex(col)->FindAtIndex(row + 1));
	}
	if (row - 1 >= 0)
	{
		nodes.Add(Grid.FindAtIndex(col)->FindAtIndex(row - 1));
	}
	if (col - 1 >= 0)
	{
		nodes.Add(Grid.FindAtIndex(col - 1)->FindAtIndex(row));
	}
	if (col + 1 < GetColumns())
	{
		nodes.Add(Grid.FindAtIndex(col + 1)->FindAtIndex(row));
	}

	return nodes;
}

bool AStar::AtEndPosition(Vector2f aEnd, GrowingArray<AStarNode*>* aClosedList)
{
	for (int i = 0; i < aClosedList->Size(); i++)
	{
		if (aClosedList->FindAtIndex(i)->GetPosition().Equals(aEnd))
		{
			return true;
		}
	}
	return false;
}

void AStar::SortByF(GrowingArray<AStarNode*>* aOpenlist)
{
	bool swapped;

	for (int i = 0; i < aOpenlist->Size(); i++)
	{
		swapped = false;
		for (int j = 0; j < aOpenlist->Size() - i - 1; j++)
		{
			if (aOpenlist->FindAtIndex(j)->F() > aOpenlist->FindAtIndex(j + 1)->F())
			{
				aOpenlist->Swap(j, j + 1);
				swapped = true;
			}
		}
		if (swapped == false) { break; }
	}
}

int AStar::GetRows()
{
	return Grid.FindAtIndex(0)->Size();
}

int AStar::GetColumns()
{
	return Grid.Size();
}
