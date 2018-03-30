#ifndef ASTAR_H
#define ASTAR_H

#include "GrowingArray.h"
#include "AStarNode.h"
class AStar
{
public:
	AStar(GrowingArray<GrowingArray<AStarNode*>> aGrid);
	~AStar();

	GrowingArray<GrowingArray<AStarNode*>> Grid;

	int GetGridRows();
	int GetGridColummns();

	bool AtEndPosition(Vector2f aEnd, GrowingArray<AStarNode*>* aClosedList);


	GrowingArray<AStarNode*> FindPath(Vector2f aStart, Vector2f aEnd);
	GrowingArray<AStarNode*> GetAdjacentNodes(AStarNode* aNode);
	
};
#endif // !ASTAR_H
