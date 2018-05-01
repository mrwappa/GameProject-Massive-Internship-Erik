#include "stdafx.h"
#include "LaserProjectile.h"
#include "Player.h"

LaserProjectile::LaserProjectile(float aX, float aY, float aAngle, bool aEnemyThreat)
{
	Init("LaserProjectile", aX, aY);
	myDepth = -9999;
	myAngle = aAngle;

	myLength = 480;
	myEnemyThreat = aEnemyThreat;

	myDamage = 4;
}


LaserProjectile::~LaserProjectile()
{

}

void LaserProjectile::Update()
{
	if (myDamage != 0)
	{
		CollisionEntity* solid = LineEdgeCollision(Vector2f(myX, myY), Vector2f(myX + Math::LenDirX(myLength, Math::DegToRad(myAngle)), myY + Math::LenDirY(myLength, Math::DegToRad(myAngle))), "Solid");
		if (solid != NULL and solid->GetName() != "GroundEdge")
		{
			myLength = Math::PointDistance(myX, myY, solid->GetX(), solid->GetY());
		}

		if (myEnemyThreat)
		{
			GrowingArray<CollisionEntity*>* enemies = LineEdgeCollisionList(Vector2f(myX, myY), Vector2f(myX + Math::LenDirX(myLength, Math::DegToRad(myAngle)), myY + Math::LenDirY(myLength, Math::DegToRad(myAngle))), "Enemy");
			if (enemies != NULL)
			{
				for (int i = 0; i < enemies->Size(); i++)
				{
					if (static_cast<Enemy*>(enemies->FindAtIndex(i))->Alive())
					{
						float dir = Math::PointDirection(Enemy::Target->GetX(), Enemy::Target->GetY(), enemies->FindAtIndex(i)->GetX(), enemies->FindAtIndex(i)->GetY() - enemies->FindAtIndex(i)->GetZ());
						enemies->FindAtIndex(i)->SetXKnock(Math::LenDirX(12, dir));
						enemies->FindAtIndex(i)->SetYKnock(Math::LenDirY(12, dir));
						enemies->FindAtIndex(i)->IncrHP(-myDamage);
					}
				}
			}
			delete enemies;
		}
		else
		{
			CollisionEntity* player = LineEdgeCollision(Vector2f(myX, myY), Vector2f(Math::LenDirX(myLength, Math::DegToRad(myAngle)), Math::LenDirY(myLength, Math::DegToRad(myAngle))), "Player");
			static_cast<Player*>(player)->Hurt(myDamage);
		}
		
	}
	
	if (myDamage == 0)
	{
		DeleteInstance(this);
	}
	myDamage = 0;
}

void LaserProjectile::Draw()
{
	//DrawLinePos(myX, myY, Math::LenDirX(myLength, myAngle), Math::LenDirY(myLength, myAngle), sf::Color::White);
	if (myDamage == 0)
	{
		DrawLine(myX, myY, myLength, myAngle, sf::Color::White);
	}
}