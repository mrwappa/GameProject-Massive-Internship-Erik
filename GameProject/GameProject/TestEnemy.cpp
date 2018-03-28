#include "stdafx.h"
#include "TestEnemy.h"


TestEnemy::TestEnemy(float aX, float aY)
{
	Init("TestEnemy", aX, aY);
	myState = Idle;
	mySprite.SetTexture("Sprites/32x32Block.png", 1);
	myColor = sf::Color::Red;


	myBoxWidth = 32;
	myBoxHeight = 32;

}


TestEnemy::~TestEnemy()
{
}

void TestEnemy::Update()
{
	myDepth = -myY;

	float dir = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
	myXSpeed = Math::LenDirX(3.0f, dir);
	myYSpeed = Math::LenDirY(3.0f, dir);

	PreventCollision("Brick");

	Move(myXSpeed, myYSpeed);

}

void TestEnemy::Draw()
{
	Entity::Draw();
	DrawBBox();
}
