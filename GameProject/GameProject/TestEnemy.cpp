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

	CollisionEntity* pAttack = ObjCollision(myX, myY, "PlayerAttack");
	myColor = sf::Color::Red;
	if (pAttack != NULL and myAttackPtr != pAttack)
	{
		myColor = sf::Color::Blue;
		dir = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
		myXKnockBack = Math::LenDirX(-16.0f, dir);
		myYKnockBack = Math::LenDirY(-16.0f, dir);
		myXSpeed = 0;
		myYSpeed = 0;
	}
	myAttackPtr = pAttack;

	float distance = Math::PointDistance(myX + myXSpeed, myY + myYSpeed, Target->GetX(), Target->GetY());
	if (distance <= 17)
	{
		myXSpeed = 0;
		myYSpeed = 0;
	}

	myXKnockBack = Math::Lerp(myXKnockBack, 0, 0.8f);
	myYKnockBack = Math::Lerp(myYKnockBack, 0, 0.8f);

	PreventCollision("Brick");
	Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);
	
	
}

void TestEnemy::Draw()
{
	Entity::Draw();
	DrawBBox();
}
