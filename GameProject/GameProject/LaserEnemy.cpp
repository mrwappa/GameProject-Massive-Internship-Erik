#include "stdafx.h"
#include "LaserEnemy.h"


LaserEnemy::LaserEnemy(float aX,float aY)
{
	Init("LaserEnemy", aX, aY);
	mySprite.SetTexture("Sprites/Enemies/spr_laserenemy.png", 1);
	myBoxWidth = 12;
	myBoxHeight = 12;

	myXScale = 2.5f;
	myYScale = myXScale;
	myZ = 10;

	myMoveSpeed = 1;

	myDamage = 2;

	myBloodColor = sf::Color(161, 197, 218);
}


LaserEnemy::~LaserEnemy()
{

}

void LaserEnemy::StateAttack()
{
	if (myState == Attack)
	{

	}
}

void LaserEnemy::Update()
{
	Enemy::Update();
}
