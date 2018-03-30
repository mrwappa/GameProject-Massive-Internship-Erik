#include "stdafx.h"
#include "AStarNode.h"

int AStarNode::NodeSize;

AStarNode::AStarNode(Vector2f aPosition, bool aWalkable)
{
	myParent = NULL;
	myPosition = aPosition;
	myDistanceToTarget = -1;
	myCost = 1;
	myWalkable = aWalkable;
}


AStarNode::~AStarNode()
{
}

Vector2f AStarNode::GetCenter()
{
	return Vector2f(myPosition.x * NodeSize + NodeSize /2, myPosition.y * NodeSize + NodeSize / 2);
}

Vector2f AStarNode::GetPosition()
{
	return myPosition;
}

float AStarNode::F()
{
	return myDistanceToTarget != -1 and myCost != -1 ? myDistanceToTarget + myCost : -1;
}

bool AStarNode::GetWalkable()
{
	return myWalkable;
}

float AStarNode::GetCost()
{
	return myCost;
}

float AStarNode::GetTargetDistance()
{
	return myDistanceToTarget;
}

AStarNode * AStarNode::GetParent()
{
	return myParent;
}

void AStarNode::SetParent(AStarNode * aNode)
{
	myParent = aNode;
}

void AStarNode::SetTargetDistance(float aX)
{
	myDistanceToTarget = aX;
}

void AStarNode::SetCost(float aCost)
{
	myCost = aCost;
}
