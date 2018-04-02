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

void TestEnemy::FindPath(float aX, float aY)
{
	if (InsideGrid(aX, aY))
	{
		myPath = AStarGrid->FindPath(SnapToGrid(myX, myY), SnapToGrid(aX, aY));
	}
}

void TestEnemy::StateAggro()
{
	myPrevState = myState;
	if (myState == Aggro)
	{
		myDirection = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
		myXSpeed = Math::LenDirX(3.0f, myDirection);
		myYSpeed = Math::LenDirY(3.0f, myDirection);

		float distance = Math::PointDistance(myX + myXSpeed, myY + myYSpeed, Target->GetX(), Target->GetY());
		if (distance <= 17)
		{
			myXSpeed = 0;
			myYSpeed = 0;
		}

		if (LineEdgeCollision(Vector2f(myX, myY), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
		{
			myState = PathFind;
			FindPath(Target->GetX(), Target->GetY());
		}
		
		CollisionEntity* brick = ObjCollision(myX, myY, "Enemy");
		if (brick != NULL)
		{
			myDirection = Math::PointDirection(myX, myY, brick->GetX(), brick->GetY());
			myXSpeed += Math::LenDirX(-1.0f, myDirection);
			myYSpeed += Math::LenDirY(-1.0f, myDirection);
		}

		PreventCollision("Brick");
		Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);
	}
}

void TestEnemy::StatePathFind()
{
	if (myState == PathFind)
	{
		if (myPath.Size() > 0)
		{
			float xTarget = myPath[myPath.Size() - 1]->GetParent()->GetCenter().x;
			float yTarget = myPath[myPath.Size() - 1]->GetParent()->GetCenter().y;

			myDirection = Math::PointDirection(myX, myY, xTarget, yTarget);
			myXSpeed = Math::LenDirX(3.0f, myDirection);
			myYSpeed = Math::LenDirY(3.0f, myDirection);
		
			Move(abs(myX - xTarget) < abs(myXSpeed) ? 0 : myXSpeed, abs(myY - yTarget) < abs(myYSpeed) ? 0 : myYSpeed);

			if (abs(myX - xTarget) <= abs(myXSpeed))
			{
				myX = xTarget;
			}
			if (abs(myY - yTarget) <= abs(myYSpeed))
			{

				myY = yTarget;
			}

			if (myX == xTarget and myY == yTarget)
			{
				if (!LineEdgeCollision(Vector2f(myX, myY), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
				{
					myPath.RemoveAll();
				}
				if (myPath.Size() > 0)
				{
					myPath.Remove(myPath[myPath.Size() - 1]);
				}
			}
		}
		else
		{
			myState = Aggro;
		}
	}
}

void TestEnemy::Update()
{
	myDepth = -myY;

	StatePathFind();
	StateAggro();

	/*CollisionEntity* brick = ObjCollision(myX + myXSpeed + myXKnockBack, myY, "Enemy");

	if (brick != NULL)
	{
		if (InstanceCollision(myX + myXSpeed + brick->GetXSpeed() + brick->GetXKnock(),
			myY, brick))
		{
			float brickX = brick->GetBoxPosition().x;
			float brickWidth = brick->GetBounds().GetWidth();

			if (myX > brickX and myXSpeed < 0)
			{
				myX = brickX + brickWidth + (myBoxWidth / 2);
			}
			if (myX < brickX and myXSpeed > 0)
			{
				myX = brickX - (myBoxWidth / 2);
			}
			myXSpeed = 0;
			myXKnockBack = 0;
		}
	}
	

	brick = ObjCollision(myX, myY + myYSpeed + myYKnockBack, "Enemy");

	if (brick != NULL)
	{
		if (InstanceCollision(myX,
			myY + myYSpeed + brick->GetYSpeed() + brick->GetYKnock(), brick))
		{
			float brickY = brick->GetBoxPosition().y;
			float brickHeight = brick->GetBounds().GetHeight();

			if (myY > brickY and myYSpeed < 0)
			{
				myY = brickY + brickHeight + (myBoxHeight / 2);
			}
			if (myY < brickY and myYSpeed > 0)
			{
				myY = brickY - (myBoxHeight / 2);
			}
			myYSpeed = 0;
			myYKnockBack = 0;
		}
	}*/
	

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

	myXKnockBack = Math::Lerp(myXKnockBack, 0, 0.25f);
	myYKnockBack = Math::Lerp(myYKnockBack, 0, 0.25f);

	
	
	
	
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
