#include "stdafx.h"
#include "CollisionEntity.h"

std::map<std::string, GrowingArray<CollisionEntity*>*> CollisionEntity::CollisionList;
GrowingArray<CollisionEntity*>* CollisionEntity::GrArrayPtr;
AStar* CollisionEntity::AStarGrid;

CollisionEntity::CollisionEntity()
{
	myZ = 0;

	myMoveSpeed = 0;
	myXSpeed = 0;
	myYSpeed = 0;
	myXKnockBack = 0;
	myYKnockBack = 0;
	myBoundingBox = RektF(0, 0, 0, 0);

	myBoxXOffset = 0;
	myBoxYOffset = 0;
	myBoxWidth = 0;
	myBoxHeight = 0;

	myHP = 0;
}


CollisionEntity::~CollisionEntity()
{
	
}

void CollisionEntity::Init(std::string aName, float aX, float aY)
{
	Entity::Init(aName, aX, aY);
	AddCollInstance(this);
}

void CollisionEntity::RemoveCollInstance(CollisionEntity* aEntity)
{
	GrArrayPtr = CollisionList.at(aEntity->GetName());
	GrArrayPtr->RemoveCyclic(aEntity);
}

void CollisionEntity::RemoveCollInstance(std::string aName, CollisionEntity* aEntity)
{
	GrArrayPtr = CollisionList.at(aName);
	GrArrayPtr->RemoveCyclic(aEntity);
}

void CollisionEntity::AddCollInstance(CollisionEntity* aEntity)
{
	if (CollisionList.count(aEntity->GetName()) == 0)
	{
		CollisionList[aEntity->GetName()] = new GrowingArray<CollisionEntity*>;
	}
	GrArrayPtr = CollisionList.at(aEntity->GetName());
	GrArrayPtr->Add(aEntity);
}

void CollisionEntity::AddCollInstance(std::string aName, CollisionEntity* aEntity)
{
	if (CollisionList.count(aName) == 0)
	{
		CollisionList[aName] = new GrowingArray<CollisionEntity*>;
	}
	GrArrayPtr = CollisionList.at(aName);
	GrArrayPtr->Add(aEntity);
}

void CollisionEntity::OnRemoval()
{
	RemoveCollInstance(this);
}

bool CollisionEntity::InsideGrid(float aX, float aY)
{
	float width = (AStarGrid->GetColumns() * AStarNode::NodeSize);
	float height = (AStarGrid->GetRows() * AStarNode::NodeSize);
	return aX <= width and aX >= 0 and aY <= height and aY >= 0;
}

Vector2f CollisionEntity::SnapToGrid(float aX, float aY)
{
	return Vector2f(floor(aX / AStarNode::NodeSize) * AStarNode::NodeSize + AStarNode::NodeSize / 2,
					floor(aY / AStarNode::NodeSize) * AStarNode::NodeSize + AStarNode::NodeSize / 2);
}

float CollisionEntity::SnapToGrid(float aX)
{
	return floor(aX / AStarNode::NodeSize) * AStarNode::NodeSize + AStarNode::NodeSize / 2;
}

Vector2f CollisionEntity::GridSnapMouse()
{
	return Vector2f(floor(Camera->GetMouseX() / AStarNode::NodeSize) * AStarNode::NodeSize + AStarNode::NodeSize / 2,
					floor(Camera->GetMouseY() / AStarNode::NodeSize) * AStarNode::NodeSize + AStarNode::NodeSize / 2);
}

bool CollisionEntity::LineIntersection(Vector2f aP1, Vector2f aP2, Vector2f aP3, Vector2f aP4)
{
	float denominator = (aP4.y - aP3.y) * (aP2.x - aP1.x) - (aP4.x - aP3.x) * (aP2.y - aP1.y);

	//Make sure the denominator is > 0, if so the lines are parallel
	if (denominator != 0)
	{
		float u_a = ((aP4.x - aP3.x) * (aP1.y - aP3.y) - (aP4.y - aP3.y) * (aP1.x - aP3.x)) / denominator;
		float u_b = ((aP2.x - aP1.x) * (aP1.y - aP3.y) - (aP2.y - aP1.y) * (aP1.x - aP3.x)) / denominator;

		//Is intersecting if u_a and u_b are between 0 and 1
		if (u_a >= 0 and u_a <= 1 and u_b >= 0 and u_b <= 1)
		{
			return true;
		}
	}

	return false;
}

bool CollisionEntity::LineToEdgeIntersection(Vector2f aStart, Vector2f aEnd, CollisionEntity * aObject)
{
	//Bounding Points Object
	Vector2f OBottomRight = aObject->GetBoxPosition() + Vector2f(aObject->GetBounds().GetWidth(), aObject->GetBounds().GetHeight());
	Vector2f OBottomLeft = aObject->GetBoxPosition() + Vector2f(0, aObject->GetBounds().GetHeight());
	Vector2f OTopLeft = aObject->GetBoxPosition();
	Vector2f OTopRight = aObject->GetBoxPosition() + Vector2f(aObject->GetBounds().GetWidth(), 0);

	Vector2f ORectangleEdges[4];
	Vector2f LineEdges[2];

	ORectangleEdges[0] = OBottomRight;
	ORectangleEdges[1] = OBottomLeft;
	ORectangleEdges[2] = OTopLeft;
	ORectangleEdges[3] = OTopRight;

	LineEdges[0] = aStart;
	LineEdges[1] = aEnd;

	//Rotate all points
	for (int i = 0; i < 4; i++)
	{
		ORectangleEdges[i] = RotatePoint(aObject->GetX() + aObject->GetXOffset(), aObject->GetY() + aObject->GetYOffset() - aObject->GetZ(), Math::DegToRad(aObject->GetAngle()),
										ORectangleEdges[i] - Vector2f(aObject->GetXOffset(), aObject->GetYOffset() - aObject->GetZ()));
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (LineIntersection(LineEdges[i], LineEdges[(i + 1) % 2], ORectangleEdges[j], ORectangleEdges[(j + 1) % 4]))
				return true;
		}
	}

	return false;
}

bool CollisionEntity::CheckBoxEdges(CollisionEntity* t, CollisionEntity* o)
{

	//Check if their Rectangles contain eachother to know if we can skip these expensive operations
	//Partially fixes problem where it can't find collision if one box is inside the other and no edges
	//are intersecting
	if (ContainRekt(t->GetBounds(), o->GetBounds()))
	{
		return true;
	}
	
	//Bounding Points t
	Vector2f TBottomRight = t->GetBoxPosition() + Vector2f(t->GetBounds().GetWidth(), t->GetBounds().GetHeight());
	Vector2f TBottomLeft = t->GetBoxPosition() + Vector2f(0, t->GetBounds().GetHeight());
	Vector2f TTopLeft = t->GetBoxPosition();
	Vector2f TTopRight = t->GetBoxPosition() + Vector2f(t->GetBounds().GetWidth(),0);

	//Bounding Points o
	Vector2f OBottomRight = o->GetBoxPosition() + Vector2f(o->GetBounds().GetWidth(), o->GetBounds().GetHeight());
	Vector2f OBottomLeft = o->GetBoxPosition() + Vector2f(0, o->GetBounds().GetHeight());
	Vector2f OTopLeft = o->GetBoxPosition();
	Vector2f OTopRight = o->GetBoxPosition() + Vector2f(o->GetBounds().GetWidth(), 0);

	Vector2f TRectangleEdges[4];
	Vector2f ORectangleEdges[4];

	TRectangleEdges[0] = TBottomRight;
	TRectangleEdges[1] = TBottomLeft;
	TRectangleEdges[2] = TTopLeft;
	TRectangleEdges[3] = TTopRight;

	ORectangleEdges[0] = OBottomRight;
	ORectangleEdges[1] = OBottomLeft;
	ORectangleEdges[2] = OTopLeft;
	ORectangleEdges[3] = OTopRight;

	//Rotate all points
	for (int i = 0; i < 4; i++)
	{
		TRectangleEdges[i] = RotatePoint(t->GetX() + t->GetXOffset(), t->GetY() + t->GetYOffset() - t->GetZ(), Math::DegToRad(t->GetAngle()), TRectangleEdges[i] - Vector2f(t->GetXOffset(), t->GetYOffset() - t->GetZ()));
		ORectangleEdges[i] = RotatePoint(o->GetX() + o->GetXOffset(), o->GetY() + o->GetYOffset() - o->GetZ(), Math::DegToRad(o->GetAngle()), ORectangleEdges[i] - Vector2f(o->GetXOffset(), o->GetYOffset() - o->GetZ()));
	}

	//Check Intersection for rectangle edges
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (LineIntersection(TRectangleEdges[i], TRectangleEdges[(i + 1) % 4], ORectangleEdges[j], ORectangleEdges[(j + 1) % 4]))
				return true;
		}
	}

	return false;
}

CollisionEntity* CollisionEntity::ObjCollision(float aX, float aY, std::string aName)
{
	if (CollisionList.count(aName) == 0)
	{
		return NULL;
	}
	UpdateBBoxManually(aX, aY);
	myAngle = fmod(myAngle, 360);

	GrArrayPtr = CollisionList.at(aName);
	for (int i = 0; i < GrArrayPtr->Size(); i++)
	{
		if (GrArrayPtr->FindAtIndex(i) != this)//no collision with itself
		{
			if (InstanceCollision(aX, aY, GrArrayPtr->FindAtIndex(i), false))
			{
				//I do not understand why the regular [] index operator is failing here
				return GrArrayPtr->FindAtIndex(i);
			}
		}
	}
	return NULL;
}

bool CollisionEntity::InstanceCollision(float aX, float aY, CollisionEntity * aObject, bool aUpdateBBox)
{
	if (aObject == NULL)
	{
		return false;
	}
	aObject->UpdateBBox();
	if (aUpdateBBox)
	{
		UpdateBBoxManually(aX, aY);
		myAngle = fmod(myAngle, 360);
	}

	float oAngle = fmod(aObject->GetAngle(), 360);;

	if ((oAngle == 0 or oAngle == 180) and (myAngle == 0 or myAngle == 180))
	{
		if (myBoundingBox.Intersect(aObject->GetBounds()))
		{
			return true;
		}
		return false;
	}

	if (CheckBoxEdges(this, aObject))
	{
		return true;
	}
	return false;
	
}

void CollisionEntity::PreventCollision(std::string aName)
{
	CollisionEntity* brick = ObjCollision(myX + myXSpeed + myXKnockBack, myY, aName);

	if (brick != NULL)
	{
		float brickBoxX = brick->GetBoxPosition().x;
		myX = floor(myX) + Math::Decimal(brickBoxX);
		for (int i = 0; i < abs(myXSpeed + myXKnockBack); i++)
		{
			if (InstanceCollision(myX + Math::Sign(myXSpeed + myXKnockBack), myY, brick)) { break; }
			myX += Math::Sign(myXSpeed + myXKnockBack);
		}
		myXSpeed = 0;
		myXKnockBack = 0;
	}

	brick = ObjCollision(myX, myY + myYSpeed + myYKnockBack, aName);

	if (brick != NULL)
	{
		float brickBoxY = brick->GetBoxPosition().y;
		myY = floor(myY) + Math::Decimal(brickBoxY);
		for (int i = 0; i < abs(myYSpeed + myYKnockBack); i++)
		{
			if (InstanceCollision(myX, myY + Math::Sign(myYSpeed + myYKnockBack), brick)) { break; }
			myY += Math::Sign(myYSpeed + myYKnockBack);
		}
		myYSpeed = 0;
		myYKnockBack = 0;
	}
}

CollisionEntity * CollisionEntity::LineEdgeCollision(Vector2f aStart, Vector2f aEnd, std::string aName)
{
	if (CollisionList.count(aName) == 0)
	{
		return NULL;
	}
	GrArrayPtr = CollisionList.at(aName);
	for (int i = 0; i < GrArrayPtr->Size(); i++)
	{
		if (LineToEdgeIntersection(aStart, aEnd, GrArrayPtr->FindAtIndex(i)))
		{
			return GrArrayPtr->FindAtIndex(i);
		}
	}
	return NULL;
}

CollisionEntity * CollisionEntity::NearestInstance(float aX, float aY, std::string aName)
{
	if (CollisionList.count(aName) == 0)
	{
		return NULL;
	}

	int nearestLength;
	CollisionEntity* colInstance = NULL;

	GrArrayPtr = CollisionList.at(aName);
	for (int i = 0; i < GrArrayPtr->Size(); i++)
	{
		int instanceLength = Math::PointDistance(aX, aY - myZ, GrArrayPtr->FindAtIndex(i)->GetX(), GrArrayPtr->FindAtIndex(i)->GetY());
		if (i == 0)
		{
			nearestLength = instanceLength;
			colInstance = GrArrayPtr->FindAtIndex(i);
		}
		else if(instanceLength < nearestLength and i != 0)
		{
			nearestLength = instanceLength;
			colInstance = GrArrayPtr->FindAtIndex(i);
		}
	}

	return colInstance;
}

bool CollisionEntity::ObjPosition(float aX, float aY, std::string aName)
{
	if (CollisionList.count(aName) == 0)
	{
		return false;
	}
	GrArrayPtr = CollisionList.at(aName);
	for (int i = 0; i < GrArrayPtr->Size(); i++)
	{
		if (aX ==  GrArrayPtr->FindAtIndex(i)->GetX() and aY == GrArrayPtr->FindAtIndex(i)->GetY())
		{
			return true;
		}
	}

	return false;
}

void CollisionEntity::UpdateBBoxManually(float aX, float aY)
{
	myBoundingBox = RektF(aX + myBoxXOffset - (myBoxWidth * abs(myXScale) / 2),
		                  aY + myBoxYOffset - (myBoxHeight * abs(myYScale) / 2) - myZ,
						  myBoxWidth * abs(myXScale),
						  myBoxHeight * abs(myYScale));
}

void CollisionEntity::UpdateBBox()
{
	myBoundingBox = RektF(myX + myBoxXOffset - (myBoxWidth * abs(myXScale) / 2),
						  myY + myBoxYOffset - (myBoxHeight * abs(myYScale) / 2) - myZ,
						  myBoxWidth * abs(myXScale),
						  myBoxHeight * abs(myYScale));
}

void CollisionEntity::DrawBBox()
{
	DrawRect(myX + myBoxXOffset, myY + myBoxYOffset - myZ, myBoxWidth * myXScale, myBoxHeight  * myYScale, myAngle, myDepth - 1, 0.5f, sf::Color::Black);
}

void CollisionEntity::Draw()
{
	if (mySprite.GetTextureWidth() > 0)
	{
		mySprite.Draw(myX, myY - myZ, myXScale, myYScale, myAngle, myDepth, myAlpha, myColor, myAnimationSpeed);
	}
}

void CollisionEntity::Move(float aXSpeed, float aYSpeed)
{
	//add slowmotion
	//change or add itself to some quadnode in the quadtree collision structure(if that is ever gonna happen)
	myPreviousX = myX;
	myPreviousY = myY;

	myX += aXSpeed;
	myY += aYSpeed;

}

bool CollisionEntity::ContainRekt(RektF aRect1, RektF aRect2)
{
	float rect1Area = aRect1.GetWidth() * aRect1.GetHeight();
	float rect2Area = aRect2.GetWidth() * aRect2.GetHeight();
	
	return rect1Area > rect2Area ? aRect1.Contains(aRect2) : aRect2.Contains(aRect1);
}

Vector2f CollisionEntity::GetBoxPosition() const
{
	return Vector2f(myBoundingBox.GetX() + myBoxXOffset,myBoundingBox.GetY() + myBoxYOffset - myZ);
}

Vector2f CollisionEntity::Rotate(float aX, float aY, float aAngle, Vector2f aPoint)
{
	return Vector2f(cos(aAngle) * (aPoint.x - aX) - sin(aAngle) * (aPoint.y - aY) + aX,
					sin(aAngle) * (aPoint.x - aX) + cos(aAngle) * (aPoint.y - aY) + aY);
}

Vector2f CollisionEntity::RotatePoint(float aX, float aY, float aAngle, Vector2f aPoint)
{
	float s = sin(aAngle);
	float c = cos(aAngle);

	// translate point back to origin:
	aPoint.x -= aX;
	aPoint.y -= aY;

	// rotate point
	float xnew = aPoint.x * c - aPoint.y * s;
	float ynew = aPoint.x * s + aPoint.y * c;

	// translate point back:
	aPoint.x = xnew + aX;
	aPoint.y = ynew + aY;
	return aPoint;
}



RektF CollisionEntity::GetBounds() const
{
	return myBoundingBox;
}

float CollisionEntity::GetZ() const
{
	return myZ;
}

float CollisionEntity::GetXOffset()
{
	return myBoxXOffset;
}

float CollisionEntity::GetYOffset()
{
	return myBoxYOffset;
}

float CollisionEntity::GetXSpeed() const
{
	return myXSpeed;
}

float CollisionEntity::GetYSpeed() const
{
	return myYSpeed;
}

float CollisionEntity::GetXKnock() const
{
	return myXKnockBack;
}

float CollisionEntity::GetYKnock() const
{
	return myYKnockBack;
}

float CollisionEntity::GetDamage() const
{
	return myDamage;
}

void CollisionEntity::SetXOffset(float aX)
{
	myBoxXOffset = aX;
}

void CollisionEntity::SetYOffset(float aY)
{
	myBoxYOffset = aY;
}

void CollisionEntity::IncrHP(float aX)
{
	myHP += aX;
}

void CollisionEntity::SetXKnock(float aX)
{
	myXKnockBack = aX;
}

void CollisionEntity::SetYKnock(float aY)
{
	myYKnockBack = aY;
}
