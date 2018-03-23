#include "stdafx.h"
#include "CollisionEntity.h"

CollisionEntity::CollisionEntity()
{
	myMovementSpeed = 0;
	myXSpeed = 0;
	myYSpeed = 0;
	myBoundingBox = RektF(0, 0, 0, 0);

	myBoxXOffset = 0;
	myBoxYOffset = 0;
	myBoxWidth = 0;
	myBoxHeight = 0;
}


CollisionEntity::~CollisionEntity()
{
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

bool CollisionEntity::CheckBoxEdges(CollisionEntity* t, CollisionEntity* o)
{
	
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
	
	//If problems arise, check here if angle needs to be converted to radians or the calculation for rotation is incorrect
	for (int i = 0; i < 4; i++)
	{
		/*TRectangleEdges[i] = Rotate(t->GetX(), t->GetY(), t->GetAngle(), TRectangleEdges[i]);
		ORectangleEdges[i] = Rotate(o->GetX(), o->GetY(), o->GetAngle(), ORectangleEdges[i]);*/
		TRectangleEdges[i].Rotate(t->GetAngle());
		ORectangleEdges[i].Rotate(o->GetAngle());
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

CollisionEntity* CollisionEntity::ObjCollision(float aX, float aY, std::string aType)
{
	return NULL;
}

bool CollisionEntity::InstanceCollision(float aX, float aY, CollisionEntity * aObject)
{
	aObject->UpdateBBox();
	UpdateBBoxManually(aX, aY);

	/*if (aObject->GetAngle() == 0 or aObject->GetAngle() == 180 and myAngle == 0 or myAngle == 180)
	{
		if (myBoundingBox.Intersect(aObject->GetBounds()))
		{
			return true;
		}
		return false;
	}*/
	if (CheckBoxEdges(this, aObject))
	{
		return true;
	}
	return false;
}

void CollisionEntity::UpdateBBoxManually(float aX, float aY)
{
	myBoundingBox = RektF(aX + myBoxXOffset - (myBoxWidth * myXScale / 2), aY + myBoxYOffset - (myBoxHeight * myYScale / 2), myBoxWidth * myXScale, myBoxHeight * myYScale);
}

void CollisionEntity::UpdateBBox()
{
	myBoundingBox = RektF(myX + myBoxXOffset - (myBoxWidth * myXScale / 2), myY + myBoxYOffset - (myBoxHeight * myYScale / 2), myBoxWidth * myXScale, myBoxHeight * myYScale);
}

void CollisionEntity::DrawBBox()
{
	DrawRect(myX + myBoxXOffset, myY + myBoxYOffset,myBoxWidth * myXScale,myBoxHeight  * myYScale,myAngle,myDepth-1,0.5f,sf::Color::Black);
}

Vector2f CollisionEntity::GetBoxPosition() const
{
	return Vector2f(myBoundingBox.GetX(),myBoundingBox.GetY());
}

Vector2f CollisionEntity::Rotate(float aX, float aY, float aAngle, Vector2f aPoint)
{
	return Vector2f(cos(aAngle) * (aPoint.x - aX) - sin(aAngle) * (aPoint.y - aY) + aX,
					sin(aAngle) * (aPoint.x - aX) + cos(aAngle) * (aPoint.y - aY) + aY);
}

RektF CollisionEntity::GetBounds() const
{
	return myBoundingBox;
}
