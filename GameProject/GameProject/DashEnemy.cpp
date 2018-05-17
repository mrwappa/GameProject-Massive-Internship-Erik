#include "stdafx.h"
#include "DashEnemy.h"


DashEnemy::DashEnemy(float aX, float aY)
{
	Init("DashEnemy", aX, aY);
	mySprite.SetTexture("Sprites/Enemies/spr_dashenemy.png", 1);

	myXScale = 2.5f;
	myYScale = myXScale;
	myBoxHeight = 8;
	myBoxWidth = 8;

	myMoveSpeed = 2;

	myShake = 0;
	myDash = false;
	myAccelerate = false;
	myDamage = 3;

	myBloodColor = sf::Color(47, 35, 48);
}


DashEnemy::~DashEnemy()
{
}

void DashEnemy::StateAggro()
{
	if (myState == Aggro)
	{
		if (myPrevState == Idle)
		{
			AttackAlarm.SetTick(Math::IRand(40, 80));
		}
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
				else
				{
					if (AttackAlarm.GetTick() == -1)
					{
						myState = Attack;
						AttackAlarm.SetTick(30);
					}
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

void DashEnemy::StateAttack()
{
	if (myState == Attack)
	{
		if (myDash)
		{
			AttackAlarm.SetTick(Math::IRand(100, 140));
			if (myAccelerate)
			{
				myMoveSpeed += 1.f;
			}
			else
			{
				myMoveSpeed = Math::Lerp(myMoveSpeed, 2, 0.2f);
				if (myMoveSpeed <= 2.5f)
				{
					myMoveSpeed = 2;
					myState = Aggro;
					myDash = false;
				}
			}

			myXSpeed = Math::LenDirX(myMoveSpeed, myDirection);
			myYSpeed = Math::LenDirY(myMoveSpeed, myDirection);
			if (myMoveSpeed >= 15.0f)
			{
				myAccelerate = false;
			}
			
			if (PreventCollision("GroundEdge"))
			{
				myMoveSpeed = 2;
				myState = Aggro;
				myDash = false;
			}
			else
			{
				if (PreventCollision("Solid","GroundEdge"))
				{
					myMoveSpeed = 2;
					Camera->ShakeScreen(6);
					myState = Aggro;
					myDash = false;
				}
			}

			if (InstanceCollision(myX, myY, Target))
			{
				myMoveSpeed = 2;
				Camera->ShakeScreen(6);
				myState = Aggro;
				myDash = false;
			}
		}
		else
		{
			myXSpeed = 0;
			myYSpeed = 0;
			myShake += 0.1f;
			if (myShake >= 3)
			{
				myDash = true;
				myAccelerate = true;
				myShake = 0;

				if(Target != NULL)
				myDirection = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
			}
		}
		
		Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);
	}
}

void DashEnemy::StateInUse()
{
	if (myState == InUse)
	{

	}
}

void DashEnemy::Update()
{
	Enemy::Update();
	if (myHP <= 0 and (myPrevState == Attack or myPrevState == Aggro))
	{
		AttackAlarm.SetTick(0);
		myShake = 0;
	}
}

void DashEnemy::EndUpdate()
{
	Enemy::EndUpdate();
	if (myState == Attack)
	{
		if (myHP != myPrevHP)
		{
			myMoveSpeed = 2;
			AttackAlarm.SetTick(Math::IRand(60, 120));
			myState = Aggro;
			myShake = 0;
			myDash = false;
		}
	}
	
}

void DashEnemy::Draw()
{
	if (myState != Grabbed and myState != InUse)
	{
		DrawShadow(myX, myY + myZ + GetHeight() / 2.3f, 1.35f + myZ / 100.0f, 0.8f + myZ / 100.0f);
	}
	if (mySprite.GetTextureWidth() > 0)
	{
		mySprite.Draw(myX + myShake * Math::IRand(-2, 2), myY - myZ + myShake * Math::IRand(-2, 2), myXScale, myYScale, myAngle, myAlpha, myColor, myAnimationSpeed);
	}
}
