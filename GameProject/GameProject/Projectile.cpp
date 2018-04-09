#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile(float aX, float aY, float aSpeed, float aDirection, bool aEnemyThreat, Enemy* aEnemy)
{
	Init("Projectile", aX, aY);
	mySprite.SetTexture("Sprites/32x32Block.png", 1);

	myXScale = 0.5f;
	myYScale = 0.5f;
	myBoxWidth = 32;
	myBoxHeight = 32;

	myAngle = Math::RadToDeg(aDirection);
	myEnemyThreat = aEnemyThreat;

	myXSpeed = Math::LenDirX(aSpeed, aDirection);
	myYSpeed = Math::LenDirY(aSpeed, aDirection);

	myIgnorable = aEnemy;
}


Projectile::~Projectile()
{
}

void Projectile::Update()
{
	myDepth = myY;

	/*if (myEnemyThreat)
	{
		Enemy* enemy = (Enemy*)ObjCollision(myX, myY, "Enemy");

		if (enemy != NULL and enemy != myIgnorable and enemy->Alive())
		{
			DeleteInstance(this);
		}
	}
	else
	{
		if (InstanceCollision(myX, myY, (CollisionEntity*)Enemy::Target))
		{
			DeleteInstance(this);
		}
	}*/

	CollisionEntity* brick = ObjCollision(myX, myY, "Solid");
	if (brick != NULL)
	{
		DeleteInstance(this);
	}

	Move(myXSpeed, myYSpeed);
}

void Projectile::Draw()
{
	Entity::Draw();
	DrawBBox();
}

bool Projectile::GetEnemyThreat()
{
	return myEnemyThreat;
}
