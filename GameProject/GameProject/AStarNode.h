#ifndef ASTARNODE_H
#define ASTARNODE_H

#include "Vector2.h"

class AStarNode
{
public:
	AStarNode(Vector2f aPosition, bool aWalkable);
	~AStarNode();

	static int NodeSize;
	//Acessors
	Vector2f GetCenter();
	Vector2f GetPosition();
	float F();
	bool GetWalkable();
	float GetCost();
	float GetTargetDistance();
	AStarNode* GetParent();

	//Modifiers
	void SetParent(AStarNode* aNode);
	void SetTargetDistance(float aX);
	void SetCost(float aCost);


private:

	AStarNode* myParent;
	Vector2f myPosition;
	float myDistanceToTarget;
	float myCost;
	float myWalkable;


};
#endif // !ASTARNODE_H