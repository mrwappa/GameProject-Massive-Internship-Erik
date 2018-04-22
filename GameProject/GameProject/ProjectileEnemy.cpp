#include "stdafx.h"
#include "ProjectileEnemy.h"


ProjectileEnemy::ProjectileEnemy(float aX, float aY)
{
	Init("ProjectileEnemy", aX, aY);
	mySprite.SetTexture("Sprites/Enemies/spr_floating_enemy1.png", 1);

	myBoxWidth = 12;
	myBoxHeight = 12;

	myXScale = 2;
	myYScale = myXScale;
	myZ = 20;
	myZTarget = 20;

	myMoveSpeed = 0.8f;

	myAttackTimer = Math::FRand(2, 5);
	myHP = 10;

	myDeflate = false;

	myDamage = 3;
}


ProjectileEnemy::~ProjectileEnemy()
{
}

void ProjectileEnemy::StateAggro()
{
	if (myState == Aggro)
	{
		myAttackTimer -= 1.0f / 60.0f;
		if (myAttackTimer <= 0)
		{
			myAttackTimer = 0.2f;
			myState = Attack;
		}

		if (Target != NULL)
		{
			myDirection = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
			myXSpeed = Math::LenDirX(myMoveSpeed, myDirection);
			myYSpeed = Math::LenDirY(myMoveSpeed, myDirection);

			float distance = Math::PointDistance(myX + myXSpeed, myY + myYSpeed, Target->GetX(), Target->GetY());
			if (distance <= 120)
			{
				myXSpeed = 0;
				myYSpeed = 0;
			}
			if (Math::PointDistance(myX, myY, Target->GetX(), Target->GetY()) < 550)
			{
				if (LineEdgeCollision(Vector2f(myX, myY), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
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

void ProjectileEnemy::StateAttack()
{
	if (myState == Attack)
	{
		myAttackTimer -= 1.0f / 60.0f;
		if (myAttackTimer <= 0)
		{
			myDirection = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY()) - Math::DegToRad(Math::IRand(-5,5) * Math::IRand(0,1));
			new Projectile(myX, myY - myZ, 7.0f, myDirection, false);
			myDeflate = true;
			myState = Aggro;
			myAttackTimer = Math::FRand(2, 5);

		}

		Move(myXKnockBack,myYKnockBack);
	}
}

void ProjectileEnemy::StateInUse()
{
	if (myState == InUse)
	{
		myAttackTimer -= 1.0f / 60.0f;

		myZ = 0;
		if (Target != NULL)
		{
			myX = Math::Lerp(myX, Target->GetX(), 0.6f);
			myY = Math::Lerp(myY, Target->GetY() - GetHeight() / 1.5f, 0.6f);
			myDepth = Target->GetDepth() + 3;
		}
		if (myAttackTimer <= 0)
		{
			myDirection = Math::PointDirection(myX, myY, Camera->GetMouseX(), Camera->GetMouseY());
			new Projectile(myX, myY - myZ, 7.0f, myDirection, true);
			myAttackTimer = 0.2f;
			myState = Grabbed;
			myDeflate = true;
		}
		
	}
}

void ProjectileEnemy::StateGrabbed()
{
	if (myPrevState == Grabbable)
	{
		myAttackTimer = 0;
	}
	if (myState == Grabbed)
	{
		myAttackTimer -= 1.0f / 60.0f;

		myZ = 0;
		if (Target != NULL)
		{
			myX = Math::Lerp(myX, Target->GetX(), 0.6f);
			myY = Math::Lerp(myY, Target->GetY() - GetHeight() / 1.5f, 0.6f);
			myDepth = Target->GetDepth() + 3;
		}
	}
	
}

void ProjectileEnemy::Update()
{
	if(Alive() and myState != Idle)
	{
		int lookDir = (myX >= Target->GetX() ? -1 : 1);
		if (myDeflate)
		{
			myXScale = Math::Lerp(myXScale, 1.2f * lookDir, 0.15f);
			myYScale = Math::Lerp(myYScale, 0.9f, 0.2f);

			if (myXScale = 1.2f)
			{
				myDeflate = false;
			}
		}
		else
		{
			if (myState != FallInAbyss)
			{
				myXScale = Math::Lerp(myXScale, 2.f * lookDir, 0.3f);
				myYScale = Math::Lerp(myYScale, 2.f, 0.2f);
			}
		}
		if (lookDir == -1 and myXScale >= 0)
		{
			myXScale = myXScale * -1;
		}
		else if (lookDir == 1 and myXScale < 0)
		{
			myXScale = myXScale * -1;
		}
	}
	else
	{
		if (myDeflate)
		{
			myXScale = Math::Lerp(myXScale, 1.2f, 0.15f);
			myYScale = Math::Lerp(myXScale, 1.5f, 0.1f);

			if (myXScale = 1.2f)
			{
				myDeflate = false;
			}
		}
		else
		{
			if (myState != FallInAbyss)
			{
				myXScale = Math::Lerp(myXScale, 2.f, 0.3f);
				myYScale = Math::Lerp(myXScale, 2.f, 0.2f);
			}
		}
	}
	

	Enemy::Update();

}

void ProjectileEnemy::Draw()
{	
	if (Target != NULL)
	{
		/*if (LineEdgeCollision(Vector2f(myX, myY), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
		{
			myLine.DrawLinePos(myX, myY - myZ, Target->GetX(), Target->GetY(), myDepth - 3, sf::Color::Red);
		}
		else
		{
			myLine.DrawLinePos(myX, myY - myZ, Target->GetX(), Target->GetY(), myDepth - 3, sf::Color::White);
		}*/
	}

	if (myState != Grabbed and myState != InUse)
	{
		if (Alive() or myState == Spawned)
		{
			DrawShadow(myX, myY + myZ, 1.35f + myZ / 100.0f, 0.8f + myZ / 100.0f);
		}
		else
		{
			DrawShadow(myX, myY + myZ + GetHeight() / 2, 1.35f + myZ / 100.0f, 0.8f + myZ / 100.0f);
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

void ProjectileEnemy::DrawGUI()
{
	//DrawFont(std::to_string((int)myHP), myX, myY - 20, 24, 1, 1, sf::Color::White);
	//DrawFont(std::to_string(myZ), myX, myY - 40, 24, 1, 1, sf::Color::White);
}
