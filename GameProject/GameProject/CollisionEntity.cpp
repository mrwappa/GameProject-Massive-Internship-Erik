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

	//Rotate Points t
	TBottomRight = RotatePoint(t->GetX(), t->GetY(), Math::DegToRad(t->GetAngle()), TBottomRight);
	TBottomLeft = RotatePoint(t->GetX(), t->GetY(), Math::DegToRad(t->GetAngle()), TBottomLeft);
	TTopLeft = RotatePoint(t->GetX(), t->GetY(), Math::DegToRad(t->GetAngle()), TTopLeft) ;
	TTopRight = RotatePoint(t->GetX(), t->GetY(), Math::DegToRad(t->GetAngle()), TTopRight);

	//Rotate Points o
	OBottomRight = RotatePoint(o->GetX(), o->GetY(), Math::DegToRad(o->GetAngle()), OBottomRight);
	OBottomLeft = RotatePoint(o->GetX(), o->GetY(), Math::DegToRad(o->GetAngle()), OBottomLeft);
	OTopLeft = RotatePoint(o->GetX(), o->GetY(), Math::DegToRad(o->GetAngle()), OTopLeft);
	OTopRight = RotatePoint(o->GetX(), o->GetY(), Math::DegToRad(o->GetAngle()), OTopRight);

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

	if ((aObject->GetAngle() == 0 or aObject->GetAngle() == 180) and (myAngle == 0 or myAngle == 180))
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

bool CollisionEntity::ContainRekt(RektF aRect1, RektF aRect2)
{
	float rect1Area = aRect1.GetWidth() * aRect1.GetHeight();
	float rect2Area = aRect2.GetWidth() * aRect2.GetHeight();
	
	return rect1Area > rect2Area ? aRect1.Contains(aRect2) : aRect2.Contains(aRect1);
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

Vector2f CollisionEntity::RotatePoint(float cx, float cy, float angle, Vector2f p)
{
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	p.x -= cx;
	p.y -= cy;

	// rotate point
	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;

	// translate point back:
	p.x = xnew + cx;
	p.y = ynew + cy;
	return p;
}



RektF CollisionEntity::GetBounds() const
{
	return myBoundingBox;
}
