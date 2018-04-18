#include "stdafx.h"
#include "Solid.h"


Solid::Solid()
{
	AddCollInstance("Solid", this);
}


Solid::~Solid()
{

}
void Solid::Init(std::string aName, float aX, float aY)
{
	CollisionEntity::Init(aName, aX, aY);

	if (InsideGrid(aX, aY))
	{
		AStarGrid->Grid.FindAtIndex(((int)aX - AStarNode::NodeSize / 2) / AStarNode::NodeSize)->FindAtIndex((int)(aY - AStarNode::NodeSize / 2) / AStarNode::NodeSize)->SetWalkable(false);
	}
}


void Solid::OnRemoval()
{
	if (AStarGrid != NULL)
	{
		if (InsideGrid(myX, myY) and !ObjPosition(myX, myY, "Solid"))
		{
			AStarGrid->Grid.FindAtIndex(((int)myX - AStarNode::NodeSize / 2) / AStarNode::NodeSize)->FindAtIndex(((int)myY - AStarNode::NodeSize / 2) / AStarNode::NodeSize)->SetWalkable(true);
		}
	}
	
	
	RemoveCollInstance("Solid", this);
	CollisionEntity::OnRemoval();
}

void Solid::Draw()
{
	int index = CollisionList["Solid"]->Find(this);
	DrawFont(std::to_string(index),myX,myY,24,1,1,sf::Color::White);
	Entity::Draw();
}

