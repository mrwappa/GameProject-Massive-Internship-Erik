#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Player* Enemy::Target;
sf::Color Enemy::GrabColor = sf::Color::Color(125,125,125,125);

Enemy::Enemy()
{
	AddCollInstance("Enemy", this);
}


Enemy::~Enemy()
{
}

void Enemy::OnRemoval()
{
	RemoveCollInstance("Enemy", this);
	CollisionEntity::OnRemoval();
}

void Enemy::StateIdle()
{
}

void Enemy::StateAggro()
{
	
}

void Enemy::StateAttack()
{

}

void Enemy::StatePathFind()
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

void Enemy::StateGrabbable()
{
	if (myState == Grabbable)
	{
		Move(myXSpeed, myYSpeed);
		myXSpeed = Math::Lerp(myXSpeed, 0, 0.2f);
		myYSpeed = Math::Lerp(myYSpeed, 0, 0.2f);
	}
}

void Enemy::StateGrabbed()
{
	if (myState == Grabbed)
	{
		if (Target != NULL)
		{
			myX = Math::Lerp(myX, Target->GetX(), 0.6f);
			myY = Math::Lerp(myY, Target->GetY() - GetHeight() / 2, 0.6f);
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
		Move(myXSpeed, myYSpeed);
		
		myXSpeed = Math::Lerp(myXSpeed, 0, 0.2f);
		myYSpeed = Math::Lerp(myYSpeed, 0, 0.2f);

		if (abs(myXSpeed) < 0.1 and abs(myYSpeed) < 0.1)
		{
			myXSpeed = 0;
			myYSpeed = 0;
			myState = Grabbable;
		}

		if (abs(myXSpeed) > 1.5f and abs(myYSpeed) > 1.5f)
		{
			Enemy* enemy = (Enemy*)ObjCollision(myX, myY, "Enemy");
			if (enemy != NULL and enemy->Alive())
			{

				enemy->IncrHP(-(4 + static_cast<CollisionEntity*>(GetObj("Player"))->GetDamage()));
				
				myDirection = Math::PointDirection(enemy->GetX(), enemy->GetY(), myX, myY);
				myXSpeed = Math::LenDirX(13, myDirection);
				myYSpeed = Math::LenDirY(13, myDirection);

				enemy->SetXKnock(-myXSpeed * 1.5f);
				enemy->SetYKnock(-myYSpeed * 1.5f);
				Camera->ShakeScreen(30.0f);

				myState = Grabbable;
			}
		}
		
	}
}

void Enemy::Throw(float aSpeed, float aDir)
{
	myDirection = aDir;
	myXSpeed = Math::LenDirX(aSpeed, aDir);
	myYSpeed = Math::LenDirY(aSpeed, aDir);
	myState = Thrown;
}

void Enemy::FindPath(float aX, float aY)
{
	if (InsideGrid(SnapToGrid(myX), SnapToGrid(myY)) and InsideGrid(SnapToGrid(aX), SnapToGrid(aY)))
	{
		myPath = AStarGrid->FindPath(SnapToGrid(myX, myY), SnapToGrid(aX, aY));
	}
}

void Enemy::SetState(int aState)
{
	myState = aState;
}

int Enemy::GetState() const
{
	return myState;
}

bool Enemy::Alive() const
{
	return myState == Idle or myState == Aggro or myState == PathFind;
}
