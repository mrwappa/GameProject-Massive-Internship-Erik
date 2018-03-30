#include "stdafx.h"
#include "TestEnemy.h"


TestEnemy::TestEnemy(float aX, float aY)
{
	Init("TestEnemy", aX, aY);
	myState = Aggro;
	mySprite.SetTexture("Sprites/32x32Block.png", 1);
	myColor = sf::Color::Red;
	
	myBoxWidth = 32;
	myBoxHeight = 32;
}


TestEnemy::~TestEnemy()
{
}

void TestEnemy::FindPath()
{

	float dir = Math::PointDirDeg(myX, myY, Target->GetX(), Target->GetY());
	float newDir = dir - Math::Choose(45,-45);
	if (LineEdgeCollision(Vector2f(myX, myY), Vector2f(Math::LenDirX(64, newDir), Math::LenDirY(64, newDir)), "Solid"))
	{
		newDir = newDir == -45 ? newDir - 45 : newDir + 45;
		newDir = Math::DegToRad(newDir);
	}

	myPath.Add(Vector2f(Math::LenDirX(64, newDir), Math::LenDirY(64, newDir)));

	if ((dir > 315 and dir <= 360) or (dir <= 45 and dir >= 0))
	{
		myPath.Add(myPath[0] + Vector2f(64, 0));
	}
	if (dir > 45 and dir <= 135)
	{
		myPath.Add(myPath[0] + Vector2f(0, -64));
	}
	if (dir > 135 and dir <= 225)
	{
		myPath.Add(myPath[0] + Vector2f(-64, 0));
	}
	if (dir > 225 and dir <= 315)
	{
		myPath.Add(myPath[0] + Vector2f(0, 64));
	}
}

void TestEnemy::Update()
{
	myDepth = -myY;

	if (myState == PathFind)
	{
		if (myPrevState != PathFind)
		{
			FindPath();
		}

		if (myPath.Size() > 0)
		{
			float dir = Math::PointDirection(myX, myY, myPath[0].x, myPath[0].y);
			myXSpeed = Math::LenDirX(3.0f, dir);
			myYSpeed = Math::LenDirY(3.0f, dir);

			if (abs(myX - myPath[0].x) <= abs(myXSpeed))
			{
				myX = myPath[0].x;
			}
			if (abs(myY - myPath[0].y) <= abs(myYSpeed))
			{
				myY = myPath[0].y;
			}
			if (myX == myPath[0].x and myY == myPath[0].y)
			{
				myPath.RemoveCyclicAtIndex(0);
			}
		}
		else
		{
			myState = Aggro;
		}
	}

	myPrevState = myState;
	if (myState == Aggro)
	{
		float dir = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
		myXSpeed = Math::LenDirX(3.0f, dir);
		myYSpeed = Math::LenDirY(3.0f, dir);

		if (LineEdgeCollision(Vector2f(myX, myY), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
		{
			myState = PathFind;
		}
	}
	

	CollisionEntity* pAttack = ObjCollision(myX, myY, "PlayerAttack");

	myColor = sf::Color::Red;
	if (pAttack != NULL and myAttackPtr != pAttack)
	{
		myColor = sf::Color::Blue;
		float dir = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
		myXKnockBack = Math::LenDirX(-19.0f, dir);
		myYKnockBack = Math::LenDirY(-19.0f, dir);
		myXSpeed = 0;
		myYSpeed = 0;
	}
	myAttackPtr = pAttack;

	float distance = Math::PointDistance(myX + myXSpeed, myY + myYSpeed, Target->GetX(), Target->GetY());
	if (distance <= 17)
	{
		myXSpeed = 0;
		myYSpeed = 0;
	}

	myXKnockBack = Math::Lerp(myXKnockBack, 0, 0.25f);
	myYKnockBack = Math::Lerp(myYKnockBack, 0, 0.25f);

	PreventCollision("Brick");
	Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);
	
}

void TestEnemy::Draw()
{
	Entity::Draw();
	DrawBBox();
	if (LineEdgeCollision(Vector2f(myX, myY), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
	{
		myLine.DrawLinePos(myX, myY, Target->GetX(), Target->GetY(), myDepth - 3, sf::Color::Red);
	}
	else
	{
		myLine.DrawLinePos(myX, myY, Target->GetX(), Target->GetY(), myDepth - 3, sf::Color::White);
	}
	
}

void TestEnemy::OnRemoval()
{

}
