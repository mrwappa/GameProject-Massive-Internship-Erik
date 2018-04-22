#include "stdafx.h"
#include "MageSpawner.h"


MageSpawner::MageSpawner(float aX, float aY)
{
	Init("MageSpawner", aX, aY);

	mySprite.SetTexture("Sprites/Enemies/spr_magespawner3.png", 8);

	myBoxWidth = 48;
	myBoxHeight = 48;
	myMoveSpeed = 1;
	myXScale = 0.58f;
	myYScale = myXScale;

	myZ = 10;
	myZTarget = 10;

	myShake = 0;
	myHP = 10;

	mySpawnAlarm.SetTick(Math::IRand(60, 200));
	myAnimationSpeed = 0.2f;

	
}

MageSpawner::~MageSpawner()
{
}

void MageSpawner::StateAggro()
{
	if (myState == Aggro)
	{
		if (myPrevState == Idle or myPrevState == Attack)
		{
			mySpawnAlarm.SetTick(Math::IRand(5, 40));
		}
		if (mySpawnAlarm.GetTick() == -1)
		{
			myState = Attack;
		}

		myMoveSpeed = 1.5f;
		if (Target != NULL)
		{
			myDirection = Math::PointDirection(myX, myY - myZ, Target->GetX(), Target->GetY());
			myXSpeed = Math::LenDirX(-myMoveSpeed, myDirection);
			myYSpeed = Math::LenDirY(-myMoveSpeed, myDirection);

			float distance = Math::PointDistance(myX + myXSpeed, myY + myYSpeed - myZ, Target->GetX(), Target->GetY());
			if (distance <= 5)
			{
				myXSpeed = 0;
				myYSpeed = 0;
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

void MageSpawner::StateGrabbed()
{
	if (myState == Grabbed)
	{
		myShake = 0;
		myZ = 0;
		if (Target != NULL)
		{
			myX = Math::Lerp(myX, Target->GetX(), 0.6f);
			myY = Math::Lerp(myY, Target->GetY() - 30, 0.6f);
			myDepth = Target->GetDepth() + 3;
		}
	}
}

void MageSpawner::StateGrabbable()
{
	if (myState == Grabbable)
	{
		//setting shake to 0 is the only reason for overriding this method...
		myShake = 0;

		if (InstanceCollision(myX, myY, Target))
		{
			myDirection = Math::PointDirection(Target->GetX(), Target->GetY(), myX, myY);
			myXSpeed = Math::LenDirX(2.f, myDirection);
			myYSpeed = Math::LenDirY(2.f, myDirection);
		}

		myAnimationSpeed = Math::Lerp(myAnimationSpeed, 0, 0.4f);
		PreventCollision("Solid");
		Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);

		myXSpeed = Math::Lerp(myXSpeed, 0, 0.2f);
		myYSpeed = Math::Lerp(myYSpeed, 0, 0.2f);
		myXKnockBack = Math::Lerp(myXKnockBack, 0, 0.2f);
		myYKnockBack = Math::Lerp(myYKnockBack, 0, 0.2f);

		Fall();
	}
}

void MageSpawner::StateFallInAbyss()
{
	if (myState == FallInAbyss)
	{
		Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);
		myXSpeed = Math::Lerp(myXSpeed, 0, 0.2f);
		myYSpeed = Math::Lerp(myYSpeed, 0, 0.2f);

		if (myXScale >= 0.2f)
		{
			myZ -= 4;
		}
		myXScale = Math::Lerp(myXScale, 0, 0.2f);
		myYScale = Math::Lerp(myYScale, 0, 0.2f);

		if (abs(myXScale) <= 0.1f)
		{
			DeleteInstance(this);
		}
	}
}
void MageSpawner::StateAttack()
{
	if (myState == Attack)
	{
		Move(myXKnockBack, myYKnockBack);
		PreventCollision("Solid");
		myShake += 0.08f;
		if (myShake >= 3)
		{
			myState = Aggro;
			mySpawnAlarm.SetTick(Math::IRand(100, 300));
			myShake = 0;
			SpawnEnemy();
		}
	}
}
void MageSpawner::StateInUse()
{
	if (myState == InUse)
	{

		myZ = 0;
		if (Target != NULL)
		{
			myX = Math::Lerp(myX, Target->GetX(), 0.6f);
			myY = Math::Lerp(myY, Target->GetY() - 30, 0.6f);
			myDepth = Target->GetDepth() + 3;
		}

		myShake += 0.08f;
		if (myShake >= 3)
		{
			myState = Grabbed;
			mySpawnAlarm.SetTick(Math::IRand(100, 300));
			myShake = 0;
			SpawnEnemy();
		}
	}

}
void MageSpawner::SpawnEnemy()
{
	int rand = Math::IRand(0, ENEMIES_SIZE-1);
	Enemy* enemy;
	switch (rand)
	{
	case Projectile:
		enemy = new ProjectileEnemy(myX,myY);
		enemy->SetState(Spawned);
		enemy->SetDirection(Math::DegToRad(Math::IRand(0, 360)));
		enemy->SetZ(30);
		break;

	case Fly:
		enemy = new TestEnemy(myX, myY);
		enemy->SetState(Spawned);
		enemy->SetDirection(Math::DegToRad(Math::IRand(0, 360)));
		enemy->SetZ(30);
		break;

	default:
		break;
	}
}
void MageSpawner::Update()
{

	if (myState == Idle)
	{
		if (mySpawnAlarm.GetTick() == -1)
		{
			mySpawnAlarm.SetTick(Math::IRand(140,200));
		}
	}
	myDepth = myY;
	
	if (Alive() and myState != Idle)
	{
		myXScale = 0.58f;
		if (myX <= Target->GetX())
		{
			myXScale = -0.58f;
		}
	}
	
	if (!Alive())
	{
		mySprite.SetTexture("Sprites/Enemies/spr_magespawner_dead.png", 1);
		myAnimationSpeed = 0;
		mySprite.SetAnimationIndex(0);
	}
	Enemy::Update();
}

void MageSpawner::Draw()
{
	if (Alive())
	{
		DrawShadow(myX, myY + 8 + myZ, 2.2f, 1.1f);
	}
	else
	{
		if(myState != Grabbed and myState != InUse)
		DrawShadow(myX, myY + 18 + myZ, 2.2f, 1.1f);
	}

	//DrawRect(myX + 2, myY + 18, 30, 10, 0, 0.6f, sf::Color::Black);
	if (mySprite.GetTextureWidth() > 0)
	{
		mySprite.Draw(myX + myShake * Math::IRand(-2, 2), myY - myZ + myShake * Math::IRand(-2, 2), myXScale, myYScale, myAngle, myAlpha, myColor, myAnimationSpeed);
	}

	DrawBBox();
}
