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
		GrowingArray<CollisionEntity*>* solids = LineEdgeCollisionList(Vector2f(myX, myY),
			Vector2f(myX + Math::LenDirX(myLength, Math::DegToRad(myAngle)), myY + Math::LenDirY(myLength, Math::DegToRad(myAngle))),
			"Solid","GroundEdge");

		if (solids != NULL and solids->Size() > 0)
		{
			float distance = Math::PointDistance(myX, myY, solids->FindAtIndex(0)->GetX(), solids->FindAtIndex(0)->GetY());
			
			for (int i = 0; i < solids->Size(); i++)
			{
				float solidDistance = Math::PointDistance(myX, myY, solids->FindAtIndex(i)->GetX(), solids->FindAtIndex(i)->GetY());
				if (solidDistance < distance)
				{
					distance = solidDistance;
				}
			}
			myLength = distance;
		}
		new LaserEffect(myX, myY, myLength, myAngle);

		if(solids != NULL)
		delete solids;

		if (myEnemyThreat)
		{
			GrowingArray<CollisionEntity*>* enemies = LineEdgeCollisionList(Vector2f(myX, myY),
				Vector2f(myX + Math::LenDirX(myLength, Math::DegToRad(myAngle)), myY + Math::LenDirY(myLength, Math::DegToRad(myAngle))),
				"Enemy");
			if (enemies != NULL and enemies->Size() != 0)
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
			if (LineToEdgeIntersection(Vector2f(myX, myY),
				Vector2f(myX + Math::LenDirX(myLength, Math::DegToRad(myAngle)), myY + Math::LenDirY(myLength, Math::DegToRad(myAngle))),Enemy::Target))
			{
				Enemy::Target->Hurt(myDamage,Math::PointDirection(myX, myY, Enemy::Target->GetX(),Enemy::Target->GetY()));
			}
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
	if (myDamage == 0)
	{
		DrawLine(myX, myY, myLength, myAngle, sf::Color::White);
	}
}