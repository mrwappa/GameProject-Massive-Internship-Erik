#include "stdafx.h"
#include "LaserEnemy.h"


LaserEnemy::LaserEnemy(float aX,float aY)
{
	Init("LaserEnemy", aX, aY);
	mySprite.SetTexture("Sprites/Enemies/spr_laserenemy.png", 1);
	myBoxWidth = 12;
	myBoxHeight = 12;

	myXScale = 2.5f;
	myYScale = myXScale;

	myZ = 15;
	myZTarget = 15;

	myMoveSpeed = 1;

	myDamage = 2;

	myBloodColor = sf::Color(161, 197, 218);
}


LaserEnemy::~LaserEnemy()
{

}

void LaserEnemy::StateAttack()
{
	if (myState == Attack)
	{
		if (myAttackAlarm.GetTick() == -1)
		{
			new LaserProjectile(myX, myY - myZ, Math::RadToDeg(myDirection), false);
			myAttackAlarm.SetTick(Math::IRand(60, 120));
			myState = Aggro;
		}


		myXSpeed = 0;
		myYSpeed = 0;
		PreventCollision("Solid");
		Move(myXKnockBack, myYKnockBack);
	}
}

void LaserEnemy::StateAggro()
{
	if (myState == Aggro)
	{
		if (myAttackAlarm.GetTick() == -1)
		{
			myAttackAlarm.SetTick(30);
			myXSpeed = 0;
			myYSpeed = 0;
			myState = Attack;
		}

		if (Target != NULL)
		{
			myDirection = Math::PointDirection(myX, myY - myZ, Target->GetX(), Target->GetY());
			myXSpeed = Math::LenDirX(myMoveSpeed, myDirection);
			myYSpeed = Math::LenDirY(myMoveSpeed, myDirection);

			float distance = Math::PointDistance(myX, myY - myZ, Target->GetX(), Target->GetY());
			if (distance <= 100)
			{
				myXSpeed = 0;
				myYSpeed = 0;
			}
			if (distance < 400)
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

void LaserEnemy::StateInUse()
{
	if (myState == InUse)
	{
		myZ = 0;
		if (Target != NULL)
		{
			myX = Math::Lerp(myX, Target->GetX(), 0.6f);
			myY = Math::Lerp(myY, Target->GetY() - GetHeight() / 1.5f, 0.6f);
			myDepth = Target->GetDepth() - 3;
		}
		if (myAttackAlarm.GetTick() == -1)
		{
			myDirection = Math::PointDirection(myX, myY - myZ, Camera->GetMouseX(), Camera->GetMouseY());
			new LaserProjectile(myX, myY - myZ, Math::PointDirDeg(myX,myY - myZ, Camera->GetMouseX(), Camera->GetMouseY()), true);
			myAttackAlarm.SetTick(30);
			myState = Grabbed;
		}
	}
}

void LaserEnemy::StateGrabbed()
{
	if (myState == Grabbed)
	{
		if (myPrevState == Grabbable)
		{
			myAttackAlarm.SetTick(0);
		}
		myZ = 0;
		if (Target != NULL)
		{
			if (Target->GetState() == Player::Dead)
			{
				myState = Grabbable;
			}
			myX = Math::Lerp(myX, Target->GetX(), 0.6f);
			myY = Math::Lerp(myY, Target->GetY() - GetHeight() / 1.5f, 0.6f);
			myDepth = Target->GetDepth() - 3;
		}
	}
}

void LaserEnemy::Update()
{
	
	Enemy::Update();
	if (myState == Idle)
	{
		myAttackAlarm.SetTick(60);
	}
}

void LaserEnemy::Draw()
{
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
	if (myState == Aggro)
	{
		DrawLine(myX + Math::LenDirX(10 + Math::IRand(-3,3), myDirection),
				 myY - myZ + Math::LenDirY(10 + Math::IRand(-3, 3), myDirection),
				 24, Math::RadToDeg(myDirection), sf::Color::White);
	}
	if (myState == Attack)
	{
		DrawLine(myX + Math::LenDirX(10, myDirection),
			myY - myZ + Math::LenDirY(10, myDirection),
			24 - ((myAttackAlarm.GetTick() / 60.f) * 24.f), Math::RadToDeg(myDirection), sf::Color::White);
	}

	
}