#include "stdafx.h"
#include "CollisionEntity.h"


CollisionEntity::CollisionEntity()
{
	myMovementSpeed = 0;
	myXSpeed = 0;
	myYSpeed = 0;
	myBoundingBox = Rectangle<float>(0, 0, 0, 0);
}


CollisionEntity::~CollisionEntity()
{
}

bool CollisionEntity::LineIntersection(Vector2<float> aP1, Vector2<float> aP2, Vector2<float> aP3, Vector2<float> aP4)
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

bool CollisionEntity::CheckBoxEdges(CollisionEntity * t, CollisionEntity * o)
{
	
	//Bounding Points t
	Vector2<float> TBottomRight = t->GetBoxPosition() + Vector2<float>(t->GetBounds().GetWidth(), t->GetBounds().GetHeight());
	Vector2<float> TBottomLeft = t->GetBoxPosition() + Vector2<float>(0, t->GetBounds().GetHeight());
	Vector2<float> TTopLeft = t->GetBoxPosition();
	Vector2<float> TTopRight = t->GetBoxPosition() + Vector2<float>(t->GetBounds().GetWidth(),0);

	//Bounding Points o
	Vector2<float> OBottomRight = o->GetBoxPosition() + Vector2<float>(o->GetBounds().GetWidth(), o->GetBounds().GetHeight());
	Vector2<float> OBottomLeft = o->GetBoxPosition() + Vector2<float>(0, o->GetBounds().GetHeight());
	Vector2<float> OTopLeft = o->GetBoxPosition();
	Vector2<float> OTopRight = o->GetBoxPosition() + Vector2<float>(o->GetBounds().GetWidth(), 0);

	Vector2<float> TRectangleEdges[4];
	Vector2<float> ORectangleEdges[4];

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
		TRectangleEdges[i].Rotate(t->GetAngle());
	}

	for (int i = 0; i < 4; i++)
	{
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

Vector2<float> CollisionEntity::GetBoxPosition() const
{
	return Vector2<float>(myBoundingBox.GetX(),myBoundingBox.GetY());
}

Rectangle<float> CollisionEntity::GetBounds() const
{
	return myBoundingBox;
}
