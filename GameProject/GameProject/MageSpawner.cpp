#include "stdafx.h"
#include "MageSpawner.h"


MageSpawner::MageSpawner(float aX, float aY)
{
	Init("MageSpawner", aX, aY);

	mySprite.SetTexture("Sprites/Enemies/spr_magespawner3.png", 8);

	myBoxWidth = 64;
	myBoxHeight = 64;
	myMoveSpeed = 1;
	myXScale = 0.58f;
	myYScale = myXScale;

	myZ = 10;
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
		myZ = 0;
		if (Target != NULL)
		{
			myX = Math::Lerp(myX, Target->GetX(), 0.6f);
			myY = Math::Lerp(myY, Target->GetY() - 30, 0.6f);
			myDepth = Target->GetDepth() + 3;
		}
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
			//myY -= 4;
			myZ -= 4;
		}
		myXScale -= 0.02f;
		myYScale -= 0.02f;

		if (myXScale <= 0.03f)
		{
			DeleteInstance(this);
		}
	}
}
void MageSpawner::StateAttack()
{
	if (myState == Attack)
	{
		
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
		if(myState != Grabbed)
		DrawShadow(myX, myY + 18 + myZ, 2.2f, 1.1f);
	}

	//DrawRect(myX + 2, myY + 18, 30, 10, 0, 0.6f, sf::Color::Black);
	CollisionEntity::Draw();
	
}
