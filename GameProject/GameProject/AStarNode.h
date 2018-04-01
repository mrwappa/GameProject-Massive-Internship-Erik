#ifndef ASTARNODE_H
#define ASTARNODE_H

#include "Vector2.h"

class AStarNode
{
public:
	AStarNode(Vector2f aPosition, bool aWalkable);
	~AStarNode();

	static int NodeSize;

	bool GetWalkable();
	float GetTargetDistance();
	float GetCost();
	Vector2f GetPosition();
	Vector2f GetCenter();
	float F();
	AStarNode* GetParent();

	void SetParent(AStarNode* aNode);
	void SetTargetDistance(float aDistance);
	void SetCost(float aCost);
	void SetWalkable(bool aWalkable);

private:

	AStarNode* myParent;
	Vector2f myPosition;
	float myDistanceToTarget;
	float myCost;
	bool myWalkable;
};
#endif // !ASTARNODE_H