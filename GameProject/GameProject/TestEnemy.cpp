#include "stdafx.h"
#include "TestEnemy.h"


TestEnemy::TestEnemy(float aX, float aY)
{
	Init("TestEnemy", aX, aY);
	mySprite.SetTexture("Sprites/Enemies/spr_fly_enemy2.png", 4);

	myAnimationSpeed = 0.2f;
	
	myXScale = 2;
	myYScale = myXScale;
	myZ = 20;
	myZTarget = 20;

	myBoxWidth = 16;
	myBoxHeight = 8;

	myMoveSpeed = Math::FRand(1.0f,1.5f);

	myHP = 10;

	myDamage = 3;

	myBloodColor = sf::Color(181, 50, 72);
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

			float distance = Math::PointDistance(myX, myY - myZ, Target->GetX(), Target->GetY());
			if (distance <= 5)
			{
				myXSpeed = 0;
				myYSpeed = 0;
			}
			if (distance < 400)
			{
				if (LineEdgeCollision(Vector2f(myX, myY - myZ), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
				{
					myState = PathFind;
					FindPath(Target->GetX(), Target->GetY());
				}
			}
		}

		Enemy* enemy = (Enemy*)ObjCollision(myX, myY, "Enemy");
		if (enemy != NULL and enemy->Alive())
		{
			myDirection = Math::PointDirection(myX, myY - myZ, enemy->GetX(), enemy->GetY());
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
			
			myEnemyTargets = ObjDistanceList(myX, myY,60, "Enemy");

			if (myEnemyTargets != NULL)
			{
				for (int i = 0; i < myEnemyTargets->Size(); i++)
				{
					if (static_cast<Enemy*>(myEnemyTargets->FindAtIndex(i))->Alive())
					{
						float dir = Math::PointDirection(Target->GetX(), Target->GetY(), myEnemyTargets->FindAtIndex(i)->GetX(), myEnemyTargets->FindAtIndex(i)->GetY() - myEnemyTargets->FindAtIndex(i)->GetZ());
						myEnemyTargets->FindAtIndex(i)->SetXKnock(Math::LenDirX(12, dir));
						myEnemyTargets->FindAtIndex(i)->SetYKnock(Math::LenDirY(12, dir));
						myEnemyTargets->FindAtIndex(i)->IncrHP(-(myDamage + Target->GetDamage()));
					}
					else
					{
						float dir = Math::PointDirection(myX, myY - myZ, myEnemyTargets->FindAtIndex(i)->GetX(), myEnemyTargets->FindAtIndex(i)->GetY() - myEnemyTargets->FindAtIndex(i)->GetZ());
						myEnemyTargets->FindAtIndex(i)->SetXKnock(Math::LenDirX(4, dir));
						myEnemyTargets->FindAtIndex(i)->SetYKnock(Math::LenDirY(4, dir));
						static_cast<Enemy*>(myEnemyTargets->FindAtIndex(i))->SetZ(Math::IRand(12,20));
					}
				}
			}
			//myEnemyTargets->RemoveAll(); 
			delete myEnemyTargets;
			myEnemyTargets = NULL;
			
			int dustParticles = Math::IRand(7, 10);
			for (int i = 0; i < dustParticles; i++)
			{
				new DustParticle(myX, myY, sf::Color(87, 194, 97));
			}
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
	//because depth is changed in Enemy Update, this is checked after
	if (myState == InUse)
	{
		myDepth = -myY -myZ - myExtraY;
	}
}

void TestEnemy::Draw()
{
	/*if (Target != NULL)
	{
		float width = -(Target->GetX() - myX);
		float height = -(Target->GetY() - myY - myZ);
		float x = myX - width / 2;
		float y = myY - height / 2;

		DrawRect(x, y, width, height, 0, 0.6f, sf::Color::Black);

		if (LineEdgeCollision(Vector2f(myX, myY - myZ), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
		{
			DrawLinePos(myX, myY - myZ, Target->GetX(), Target->GetY(), sf::Color::Red);
		}
		else
		{
			DrawLinePos(myX, myY - myZ, Target->GetX(), Target->GetY(), sf::Color::White);
		}
	}*/

	if (myState != Grabbed)
	{
		if (Alive() or myState == Spawned)
		{
			DrawShadow(myX, myY + myZ, 1.5f + myZ / 100.0f, 0.8f + myZ / 100.0f);
		}
		else
		{
			
			if (Alive() or myState == Spawned)
			{
				DrawShadow(myX, myY + myZ, 1.5f + myZ / 100.0f, 0.8f + myZ / 100.0f);
			}
			else
			{
				if (myState == InUse)
				{
					if (myPrevState != Grabbed)
					{
						DrawShadow(myX, myY + myZ + GetHeight() / 2 + 5, 1.5f + myZ / 100.0f, 0.8f + myZ / 100.0f);
					}
				}
				else if (myState ==+ Grabbed)
				{
					if (myPrevState != InUse)
					{
						DrawShadow(myX, myY + myZ + GetHeight() / 2, 1.5f + myZ / 100.0f, 0.8f + myZ / 100.0f);
					}
				}
				else
				{
					DrawShadow(myX, myY + myZ + GetHeight() / 2, 1.5f + myZ / 100.0f, 0.8f + myZ / 100.0f);
				}
			}
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

