#include "stdafx.h"
#include "Projectile.h"


Projectile::Projectile(float aX, float aY, float aSpeed, float aDirection, bool aEnemyThreat)
{
	Init("Projectile", aX, aY);
	mySprite.SetTexture("Sprites/Player/spr_circle.png", 1);

	myXScale = 0.5f;
	myYScale = myXScale;
	myBoxWidth = 32;
	myBoxHeight = 32;

	myAngle = Math::RadToDeg(aDirection);
	myEnemyThreat = aEnemyThreat;

	myXSpeed = Math::LenDirX(aSpeed, aDirection);
	myYSpeed = Math::LenDirY(aSpeed, aDirection);
	myDamage = 4;
}


Projectile::~Projectile()
{
}

void Projectile::Update()
{
	myDepth = myY;

	CollisionEntity* brick = ObjCollision(myX, myY, "Solid");
	if (brick != NULL and brick->GetName() != "GroundEdge")
	{
		DeleteInstance(this);
	}

	if (myX < Camera->GetX() - (Camera->GetViewWidth() / 2) - 50 or myX > Camera->GetX() + (Camera->GetViewWidth() / 2) + 50 or
		myY < Camera->GetY() - (Camera->GetViewHeight() / 2) - 50 or myY > Camera->GetY() + (Camera->GetViewHeight() / 2) + 50)
	{
		DeleteInstance(this);
	}

	Move(myXSpeed, myYSpeed);
}

void Projectile::Draw()
{
	Entity::Draw();
	//DrawBBox();
}

bool Projectile::GetEnemyThreat()
{
	return myEnemyThreat;
}
