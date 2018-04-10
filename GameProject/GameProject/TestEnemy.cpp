#include "stdafx.h"
#include "TestEnemy.h"


TestEnemy::TestEnemy(float aX, float aY)
{
	Init("TestEnemy", aX, aY);
	myState = Aggro;
	mySprite.SetTexture("Sprites/Enemies/spr_fly_enemy.png", 4);

	myAnimationSpeed = 0.2f;
	
	myXScale = 2;
	myYScale = myXScale;
	myZ = 20;

	myBoxWidth = 16;
	myBoxHeight = 8;

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
			myDirection = Math::PointDirection(myX, myY - myZ, Target->GetX(), Target->GetY());
			myXSpeed = Math::LenDirX(myMoveSpeed, myDirection);
			myYSpeed = Math::LenDirY(myMoveSpeed, myDirection);

			float distance = Math::PointDistance(myX + myXSpeed, myY + myYSpeed - myZ, Target->GetX(), Target->GetY());
			if (distance <= 5)
			{
				myXSpeed = 0;
				myYSpeed = 0;
			}

			if (LineEdgeCollision(Vector2f(myX, myY - myZ), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
			{
				myState = PathFind;
				FindPath(Target->GetX(), Target->GetY());
			}
		}

		CollisionEntity* brick = ObjCollision(myX, myY, "Enemy");
		if (brick != NULL)
		{
			myDirection = Math::PointDirection(myX, myY - myZ, brick->GetX(), brick->GetY());
			myXSpeed += Math::LenDirX(-1.0f, myDirection);
			myYSpeed += Math::LenDirY(-1.0f, myDirection);
		}

		PreventCollision("Solid");
		Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);
	}
}

void TestEnemy::StateInUse()
{
	if (myState == InUse)
	{
		if (myZ <= -1)
		{
			myRetract = true;
			myZ = -0.99f;
			Camera->ShakeScreen(8);
			
			myEnemyTargets = ObjDistanceList(myX, myY,80, "Enemy");

			if (myEnemyTargets != NULL)
			{
				for (int i = 0; i < myEnemyTargets->Size(); i++)
				{
					if (static_cast<Enemy*>(myEnemyTargets->FindAtIndex(i))->Alive())
					{
						float dir = Math::PointDirection(myX, myY - myZ, myEnemyTargets->FindAtIndex(i)->GetX(), myEnemyTargets->FindAtIndex(i)->GetY() - myEnemyTargets->FindAtIndex(i)->GetZ());
						myEnemyTargets->FindAtIndex(i)->SetXKnock(Math::LenDirX(15, dir));
						myEnemyTargets->FindAtIndex(i)->SetYKnock(Math::LenDirY(15, dir));
						myEnemyTargets->FindAtIndex(i)->IncrHP(-(myDamage + Target->GetDamage()));
					}
				}
			}
			//myEnemyTargets->RemoveAll(); 
			delete myEnemyTargets;
			myEnemyTargets = NULL;
			
			
		}
		if (!myRetract)
		{
			myZ -= 2.2f;
			myExtraX += Math::LenDirX(7, myDirection);
			myExtraY += Math::LenDirY(7, myDirection);
		}
		else
		{
			myZ += 1.4f;
			myExtraX -= Math::LenDirX(7, myDirection);
			myExtraY -= Math::LenDirY(7, myDirection);

			if (myZ >= GetHeight() / 2.0f)
			{
				myState = Grabbed;
				myRetract = false;
				myExtraX = 0;
				myExtraY = 0;
			}
		}
		myX = Target->GetX() + myExtraX;
		myY = Target->GetY() + myExtraY - myZ;
	}
}

void TestEnemy::Update()
{
	Enemy::Update();
}

void TestEnemy::Draw()
{
	
	if (Target != NULL)
	{
		/*if (LineEdgeCollision(Vector2f(myX, myY - myZ), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
		{
			myLine.DrawLinePos(myX, myY - myZ, Target->GetX(), Target->GetY(), myDepth - 3, sf::Color::Red);
		}
		else
		{
			myLine.DrawLinePos(myX , myY - myZ, Target->GetX(), Target->GetY(), myDepth - 3, sf::Color::White);
		}*/
	}
	if (myState != Grabbed)
	{
		if (Alive())
		{
			DrawShadow(myX, myY + myZ, 1.5f + myZ / 100.0f, 0.8f + myZ / 100.0f);
		}
		else
		{
			DrawShadow(myX, myY + myZ + GetHeight() / 2, 1.5f + myZ / 100.0f, 0.8f + myZ / 100.0f);
		}
	}
	
	CollisionEntity::Draw();
	//DrawBBox();

	/*for (int i = 0; i < myPath.Size(); i++)
	{
		myLine.DrawLinePos(myPath[i]->GetCenter().x, myPath[i]->GetCenter().y, myPath[i]->GetParent()->GetCenter().x, myPath[i]->GetParent()->GetCenter().y,
							myDepth, sf::Color::White);
	}*/
}

void TestEnemy::DrawGUI()
{
	//DrawFont(std::to_string((int)myHP), myX, myY , 24, 1, 1, sf::Color::White);
	//DrawFont(std::to_string(myZ), myX, myY - 40, 24, 1, 1, sf::Color::White);
}

