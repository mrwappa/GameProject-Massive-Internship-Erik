#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "World.h"

Player* Enemy::Target;
sf::Color Enemy::GrabColor = sf::Color::Color(125,125,125,125);

Enemy::Enemy()
{
	World::EnemyCount++;
	myHP = 10;
	myZSpeed = 3.0f;
	myState = Idle;
	AddCollInstance("Enemy", this);
	myShadow.SetTexture("Sprites/Player/spr_circle.png", 1);
	myJustThrown = false;

	mySpawnSpeed = 5;
}

Enemy::~Enemy()
{

}

void Enemy::Init(std::string aName, float aX, float aY)
{
	CollisionEntity::Init(aName, aX, aY);
	myPrevHP = myHP;
}

void Enemy::OnRemoval()
{
	RemoveCollInstance("Enemy", this);
	CollisionEntity::OnRemoval();
}

void Enemy::StateIdle()
{
	if (myState == Idle)
	{
		if (myWalkAlarm.GetTick() == -1)
		{
			myDirection = Math::DegToRad(Math::IRand(0, 360));
			float length = Math::IRand(40, 100);
			myWalkPoint = Vector2f(myX + Math::LenDirX(length,myDirection),myY + Math::LenDirY(length,myDirection));
			myWalkAlarm.SetTick(Math::IRand(60, 120));
		}
		
		myDirection = Math::PointDirection(myX, myY, myWalkPoint.x, myWalkPoint.y);
		myXSpeed = Math::LenDirX(myMoveSpeed / 1.5f, myDirection);
		myYSpeed = Math::LenDirY(myMoveSpeed / 1.5f, myDirection);

		if (PreventCollision("Solid"))
		{
			myDirection = Math::DegToRad(Math::IRand(0, 360));
			float length = Math::IRand(40, 100);
			myWalkPoint = Vector2f(myX + Math::LenDirX(length, myDirection),myY + Math::LenDirY(length, myDirection));
			myWalkAlarm.SetTick(Math::IRand(60, 120));
		}

		if (Math::PointDistance(myX, myY, myWalkPoint.x, myWalkPoint.y) <= Math::PointDistance(0, 0, myXSpeed, myYSpeed))
		{
			myXSpeed = 0;
			myYSpeed = 0;
			myX = myWalkPoint.x;
			myY = myWalkPoint.y;
		}

		Move(myXSpeed + myXKnockBack,myYSpeed + myYKnockBack);

		if (Target != NULL and Math::PointDistance(myX, myY, Target->GetX(), Target->GetY()) < 240)
		{
			if (!LineEdgeCollision(Vector2f(myX, myY), Vector2f(Target->GetX(), Target->GetY()), "Solid", "GroundEdge"))
			{
				myState = Aggro;
			}
		}
	}
}

void Enemy::StateSpawned()
{
	if (myState == Spawned)
	{
		CollisionEntity* groundEdge = ObjCollision(myX, myY, "GroundEdge");
		Fall();
		if (myZ <= 12 and mySpawnSpeed <= 0.5)
		{
			myState = Idle;
			if (ObjCollision(myX, myY, "LevelSection") == NULL)
			{
				myState = FallInAbyss;
			}
			
			if (groundEdge != NULL)
			{
				if(Target != NULL)
				myDirection = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());

				myXKnockBack = Math::LenDirX(3, myDirection);
				myYKnockBack = Math::LenDirY(3, myDirection);
			}
		}

		if (groundEdge != NULL)
		{
			if (Target != NULL)
			myDirection = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());

			myXKnockBack = Math::LenDirX(3, myDirection);
			myYKnockBack = Math::LenDirY(3, myDirection);
		}

		mySpawnSpeed = Math::Lerp(mySpawnSpeed, 0, 0.2f);
		myXSpeed = Math::LenDirX(mySpawnSpeed, myDirection);
		myYSpeed = Math::LenDirX(mySpawnSpeed, myDirection);
		PreventCollision("Solid");
		Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);
		
	}
}

void Enemy::StateAggro()
{
	
}

void Enemy::StateAttack()
{

}

void Enemy::StatePathFind()
{
	//should probably be at EndUpdate()
	myPrevState = myState;

	if (myState == PathFind)
	{
		if (myPath.Size() > 0)
		{
			float xTarget = myPath[myPath.Size() - 1]->GetParent()->GetCenter().x;
			float yTarget = myPath[myPath.Size() - 1]->GetParent()->GetCenter().y;

			//It's possible that lerping to the position is a better solution here
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

				if (!LineEdgeCollision(Vector2f(myX, myY - myZ), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
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

void Enemy::StateGrabbable()
{
	if (myState == Grabbable)
	{
		if (InstanceCollision(myX, myY, Target))
		{
			myDirection = Math::PointDirection(Target->GetX(), Target->GetY(), myX, myY);
			myXSpeed = Math::LenDirX(2.f, myDirection);
			myYSpeed = Math::LenDirY(2.f, myDirection);
		}

		myAnimationSpeed = Math::Lerp(myAnimationSpeed,0,0.4f);
		PreventCollision("Solid");
		Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);

		myXSpeed = Math::Lerp(myXSpeed, 0, 0.2f);
		myYSpeed = Math::Lerp(myYSpeed, 0, 0.2f);
		myXKnockBack = Math::Lerp(myXKnockBack, 0, 0.2f);
		myYKnockBack = Math::Lerp(myYKnockBack, 0, 0.2f);

		Fall();
	}
}

void Enemy::StateGrabbed()
{
	if (myState == Grabbed)
	{
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

void Enemy::StateInUse()
{

}

void Enemy::StateThrown()
{
	if (myState == Thrown)
	{
		CollisionEntity* brick = ObjCollision(myX, myY, "Solid");

		if (brick != NULL and myJustThrown and myYSpeed > 0)
		{
			myThrowAlarm.SetTick(5);
		}
		myJustThrown = false;
		if (brick != NULL and myThrowAlarm.GetTick() == -1 and brick->GetName() != "GroundEdge")
		{
			myXSpeed = -myXSpeed / 1.7f;
			myXKnockBack = -myXKnockBack / 1.7f;
			myYSpeed = -myYSpeed / 1.7f;
			myYKnockBack = -myYKnockBack / 1.7f;

			myThrowAlarm.SetTick(5);
			Camera->ShakeScreen(5.0f);

			int dustParticles = Math::IRand(7, 10);
			for (int i = 0; i < dustParticles; i++)
			{
				new DustParticle(myX, myY, sf::Color(87, 113, 156));
			}
		}

		Move(myXSpeed, myYSpeed);
		
		myXSpeed = Math::Lerp(myXSpeed, 0, 0.2f);
		myYSpeed = Math::Lerp(myYSpeed, 0, 0.2f);
		Fall();

		if (abs(myXSpeed) < 0.5f and abs(myYSpeed) < 0.5f)
		{
			myXSpeed = 0;
			myYSpeed = 0;
			myState = Grabbable;
		}

		if (abs(myXSpeed) > 1.5f or abs(myYSpeed) > 1.5f)
		{
			Enemy* enemy = (Enemy*)ObjCollision(myX, myY, "Enemy");
			if (Target != NULL and enemy != NULL and enemy->Alive())
			{
				enemy->IncrHP(-(4 + Target->GetDamage()));
				
				//myDirection = Math::PointDirection(enemy->GetX(), enemy->GetY(), myX, myY - myZ);
				myDirection = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
				myXSpeed = Math::LenDirX(13, myDirection);
				myYSpeed = Math::LenDirY(13, myDirection);

				enemy->SetXKnock(-myXSpeed * 1.5f);
				enemy->SetYKnock(-myYSpeed * 1.5f);
				Camera->ShakeScreen(25.0f);

				myState = Grabbable;
			}
		}
		
	}
}

void Enemy::StateFallInAbyss()
{
	if (myState == FallInAbyss)
	{
		Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);
		myXSpeed = Math::Lerp(myXSpeed, 0, 0.25f);
		myYSpeed = Math::Lerp(myYSpeed, 0, 0.25f);

		if (myXScale >= 0.2f)
		{
			myZ -= 4;
		}
		myXScale -= 0.07f;
		myYScale -= 0.07f;

		if (myXScale <= 0.08f)
		{
			DeleteInstance(this);
		}
	}
}

void Enemy::BeginUpdate()
{

	myPrevHP = myHP;

}

void Enemy::Update()
{
	myDepth = -myY - myZ;
	if (myState == FallInAbyss)
	{
		myDepth = -myY - myZ + 200;
	}
	
	StatePathFind();
	StateIdle();
	StateSpawned();
	StateAggro();
	StateAttack();
	StateGrabbable();
	StateGrabbed();
	StateThrown();
	StateInUse();
	StateFallInAbyss();
	
	if (Alive())
	{
		PlayerAttack* pAttack = (PlayerAttack*)ObjCollision(myX, myY, "PlayerAttack");
		Projectile* projectile = (Projectile*)ObjCollision(myX, myY, "Projectile");

		//Hit by Projectile
		if (projectile != NULL and projectile->GetEnemyThreat())
		{
			myDirection = Math::PointDirection(projectile->GetX(), projectile->GetY(), myX, myY - myZ);
			myXKnockBack = Math::LenDirX(10, myDirection);
			myYKnockBack = Math::LenDirY(10, myDirection);

			myHP -= projectile->GetDamage();

			DeleteInstance(projectile);
			int dustParticles = Math::IRand(5, 7);
			for (int i = 0; i < dustParticles; i++)
			{
				new DustParticle(myX, myY, sf::Color(87, 113, 156));
			}
		}

		//Hit by PlayerAttack
		if (Target != NULL and pAttack != NULL and myAttackPtr != pAttack)
		{
			float dir = Math::PointDirection(myX, myY - myZ, Target->GetX(), Target->GetY());
			myXKnockBack = Math::LenDirX(-12.0f, dir);
			myYKnockBack = Math::LenDirY(-12.0f, dir);
			myXSpeed = 0;
			myYSpeed = 0;
			myHP -= pAttack->GetDamage();
			if (myState == PathFind or myState == Idle)
			{
				myState = Aggro;
			}
		}
		myAttackPtr = pAttack;
	}

	if (Alive())
	{
		myZ = Math::Lerp(myZ, myZTarget, 0.3f);
	}
	
	if (myHP <= 0 and Alive())
	{
		World::Score += 6000;
		World::EnemyCount--;
		myYKnockBack = 0;
		myXKnockBack = 0;
		myXSpeed = 0;
		myYSpeed = 0;
		myState = Grabbable;
	}



	if (myState == Thrown or myState == Grabbable)
	{
		if (ObjCollision(myX, myY, "LevelSection") == NULL)
		{
			myState = FallInAbyss;
		}
	}

	myXKnockBack = Math::Lerp(myXKnockBack, 0, 0.25f);
	myYKnockBack = Math::Lerp(myYKnockBack, 0, 0.25f);

	myColor = sf::Color::White;
	if (myHurtAlarm.GetTick() != -1)
	{
		myColor = sf::Color(Math::IRand(0, 255), Math::IRand(0, 255), Math::IRand(0, 255), 255);
	}
	
	if (myPrevState == Grabbed)
	{
		if (Target == NULL)
		{
			myState = Grabbable;
			myZ = 22;
		}
	}
}

void Enemy::EndUpdate()
{
	//Because of Update order, I have to check this twice
	if (myPrevHP != myHP)
	{
		if (myState == Idle)
		{
			myState = Aggro;
		}
		myHurtAlarm.SetTick(15);
		int dustParticles = Math::IRand(6, 9);
		for (int i = 0; i < dustParticles; i++)
		{
			new DustParticle(myX, myY, myBloodColor);
		}
	}
}

void Enemy::Throw(float aSpeed, float aDir)
{
	myZ = 15;
	myDirection = aDir;
	myXSpeed = Math::LenDirX(aSpeed, aDir);
	myYSpeed = Math::LenDirY(aSpeed, aDir);
	myState = Thrown;
	myJustThrown = true;
}

void Enemy::Fall()
{
	myZSpeed -= 0.35f;
	if ((myZ + myZSpeed) < 0)
	{
		while (myZ + Math::Sign(myZSpeed) > 0)
		{
			myZ += Math::Sign(myZSpeed);
		}
		if (abs(myZSpeed) > 1.5f)
		{
			myZSpeed *= -0.74f;
		}
		else
		{
			myZSpeed = 0;
		}
	}
	else
	{
		myZ += myZSpeed;
	}
}

void Enemy::FindPath(float aX, float aY)
{
	if (InsideGrid(SnapToGrid(myX), SnapToGrid(myY)) and InsideGrid(SnapToGrid(aX), SnapToGrid(aY)))
	{
		myPath = AStarGrid->FindPath(SnapToGrid(myX, myY - myZ), SnapToGrid(aX, aY));
	}
}

void Enemy::DrawShadow(float aX, float aY, float aXScale, float aYScale)
{
	if (myState != FallInAbyss)
	{
		myShadow.Draw(aX, aY, aXScale, aYScale, 0, 0.6f, sf::Color::Black, 0);
	}
	
}

void Enemy::SetState(int aState)
{
	myState = aState;
}

void Enemy::SetPrevState(int aState)
{
	myPrevState = aState;
}

void Enemy::SetZ(float aZ)
{
	myZ = aZ;
}

int Enemy::GetState() const
{
	return myState;
}

bool Enemy::Alive() const
{
	return myState == Idle or myState == Aggro or myState == PathFind or myState == Attack;
}