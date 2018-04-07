#include "stdafx.h"
#include "PlayerAttack.h"


PlayerAttack::PlayerAttack(float aX, float aY, Player* aTarget)
{
	Init("PlayerAttack", aX, aY);
	mySprite.SetTexture("Sprites/Player/spr_playerattack.png", 8);
	
	myColor = sf::Color::Color(158,52,41);
	myAnimationSpeed = 0.6f;
	myXScale = 2;
	myYScale = Math::Choose(myXScale,-myXScale);
	myBoxWidth = 7;
	myBoxHeight = 18;

	myDamage = 4;

	myTarget = aTarget;
}

PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Update()
{
	myDepth = myY;

	if (mySprite.GetAnimationIndex() == mySprite.GetNrOfFrames() - 1 and myTarget != NULL)
	{
		myTarget->PAttack = NULL;
		DeleteInstance(this);
	}

	
}

void PlayerAttack::Draw()
{
	Entity::Draw();
	DrawBBox();
}
