#ifndef ASTAR_H
#define ASTAR_H

#include "AStarNode.h"
#include "GrowingArray.h"


class AStar
{
public:
	AStar(float aRows, float aColumns);
	~AStar();
	
	GrowingArray<GrowingArray<AStarNode*>*> Grid;
	void DestroyGrid();

	GrowingArray<AStarNode*> FindPath(Vector2f aStart, Vector2f aEnd);
	GrowingArray<AStarNode*> GetAdjacentNodes(AStarNode* aNode);
	bool AtEndPosition(Vector2f aEnd, GrowingArray<AStarNode*>* aClosedList);

	void SortByF(GrowingArray<AStarNode*>* aOpenlist);

	int GetRows();
	int GetColumns();

};
#endif // !ASTAR_H