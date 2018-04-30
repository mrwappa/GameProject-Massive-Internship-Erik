#include "stdafx.h"
#include "LaserProjectile.h"


LaserProjectile::LaserProjectile(float aX, float aY, float aAngle, bool aEnemyThreat)
{
	Init("LaserProjectile", aX, aY);
	myDepth = 9999;
	myAngle = aAngle;

	myLength = 180;
}


LaserProjectile::~LaserProjectile()
{

}

void LaserProjectile::Draw()
{
	//DrawLinePos(myX, myY, Math::LenDirX(myLength, myAngle), Math::LenDirY(myLength, myAngle), sf::Color::White);
	DrawLine(myX, myY, myLength, myAngle, sf::Color::White);

	DeleteInstance(this);
}