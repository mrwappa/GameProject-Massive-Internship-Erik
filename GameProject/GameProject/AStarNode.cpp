#include "stdafx.h"
#include "AStarNode.h"

int AStarNode::NodeSize;

AStarNode::AStarNode(Vector2f aPosition, bool aWalkable)
{
	myParent = NULL;
	myPosition = aPosition;
	myWalkable = aWalkable;
	myDistanceToTarget = -1;
	myCost = 1;

}


AStarNode::~AStarNode()
{
}

bool AStarNode::GetWalkable()
{
	return myWalkable;
}

float AStarNode::GetTargetDistance()
{
	return myDistanceToTarget;
}

float AStarNode::GetCost()
{
	return myCost;
}

Vector2f AStarNode::GetPosition()
{
	return myPosition;
}

Vector2f AStarNode::GetCenter()
{
	return Vector2f(myPosition.x * NodeSize + NodeSize / 2, myPosition.y * NodeSize + NodeSize / 2);
}

float AStarNode::F()
{
	if (myDistanceToTarget != -1 and myCost != -1)
	{
		return myDistanceToTarget + myCost;
	}
	return -1;
}

AStarNode * AStarNode::GetParent()
{
	return myParent;
}

void AStarNode::SetParent(AStarNode * aNode)
{
	myParent = aNode;
}

void AStarNode::SetTargetDistance(float aDistance)
{
	myDistanceToTarget = aDistance;
}

void AStarNode::SetCost(float aCost)
{
	myCost = aCost;
}

void AStarNode::SetWalkable(bool aWalkable)
{
	myWalkable = aWalkable;
}
