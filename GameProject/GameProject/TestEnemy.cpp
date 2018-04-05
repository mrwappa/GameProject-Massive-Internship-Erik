#include "stdafx.h"
#include "TestEnemy.h"


TestEnemy::TestEnemy(float aX, float aY)
{
	Init("TestEnemy", aX, aY);
	myState = Aggro;
	mySprite.SetTexture("Sprites/32x32Block.png", 1);
	
	myBoxWidth = 32;
	myBoxHeight = 32;

	myMoveSpeed = Math::FRand(2.0f,3.0f);

	myHP = 10;
}


TestEnemy::~TestEnemy()
{
}

void TestEnemy::StateAggro()
{
	myPrevState = myState;
	if (myState == Aggro)
	{
		if (Target != NULL)
		{
			myDirection = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
			myXSpeed = Math::LenDirX(myMoveSpeed, myDirection);
			myYSpeed = Math::LenDirY(myMoveSpeed, myDirection);

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
			myXSpeed = Math::LenDirX(myMoveSpeed, myDirection);
			myYSpeed = Math::LenDirY(myMoveSpeed, myDirection);
		
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

void TestEnemy::StateGrabbable()
{
	if (myState == Grabbable)
	{
		Move(myXSpeed, myYSpeed);
		myXSpeed = Math::Lerp(myXSpeed, 0, 0.5f);
		myYSpeed = Math::Lerp(myYSpeed, 0, 0.2f);
	}
}

void TestEnemy::StateGrabbed()
{
	if (myState == Grabbed)
	{
		if(Target != NULL)
		{
			myX = Math::Lerp(myX,Target->GetX(),0.6f);
			myY = Math::Lerp(myY, Target->GetY() - GetHeight() / 2,0.6f);
			myDepth = Target->GetDepth() - 3;
		}
	}
}

void TestEnemy::Update()
{
	myColor = sf::Color::Red;

	myDepth = -myY;

	StatePathFind();
	StateAggro();
	StateGrabbable();
	StateGrabbed();
	StateThrown();

	PlayerAttack* pAttack = (PlayerAttack*)ObjCollision(myX, myY, "PlayerAttack");

	if (myState != Grabbable and myState != Grabbed and myState != InUse)
	{
		if (pAttack != NULL and myAttackPtr != pAttack)
		{
			float dir = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
			myXKnockBack = Math::LenDirX(-19.0f, dir);
			myYKnockBack = Math::LenDirY(-19.0f, dir);
			myXSpeed = 0;
			myYSpeed = 0;
			myHP -= pAttack->GetDamage();
			if (myState == PathFind)
			{
				myState = Aggro;
			}
		}
		myAttackPtr = pAttack;
	}
	
	if (myHP <= 0 and Alive())
	{
		myState = Grabbable;
	}

	myXKnockBack = Math::Lerp(myXKnockBack, 0, 0.25f);
	myYKnockBack = Math::Lerp(myYKnockBack, 0, 0.25f);
}

void TestEnemy::Draw()
{
	Entity::Draw();
	DrawBBox();
	if (Target != NULL)
	{
		if (LineEdgeCollision(Vector2f(myX, myY), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
		{
			myLine.DrawLinePos(myX, myY, Target->GetX(), Target->GetY(), myDepth - 3, sf::Color::Red);
		}
		else
		{
			myLine.DrawLinePos(myX, myY, Target->GetX(), Target->GetY(), myDepth - 3, sf::Color::White);
		}
	}
	
	//rip drawing multiple lines because of my and SFMLs bad design
	for (int i = 0; i < myPath.Size(); i++)
	{
		myLine.DrawLinePos(myPath[i]->GetCenter().x, myPath[i]->GetCenter().y, myPath[i]->GetParent()->GetCenter().x, myPath[i]->GetParent()->GetCenter().y,
							myDepth, sf::Color::White);
	}
	
	
}

void TestEnemy::DrawGUI()
{
	DrawFont(std::to_string((int)myHP), myX, myY - 20, 24, 1, 1, sf::Color::White);
}

void TestEnemy::OnRemoval()
{

}
