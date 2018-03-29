#include "stdafx.h"
#include "PlayerAttack.h"


PlayerAttack::PlayerAttack(float aX, float aY, Player* aTarget)
{
	Init("PlayerAttack", aX, aY);
	mySprite.SetTexture("Sprites/Player/spr_playerattack.png", 8);
	
	myColor = sf::Color::Color(158,52,41);
	myAnimationSpeed = 0.2f;
	myXScale = 2;
	myYScale = Math::Choose(myXScale,-myXScale);
	myBoxWidth = 10;
	myBoxHeight = 23;

	myTarget = aTarget;
}

PlayerAttack::~PlayerAttack()
{
}

void PlayerAttack::Update()
{
	myDepth = -myY;

	if (mySprite.GetAnimationIndex() == mySprite.GetNrOfFrames() - 1)
	{
		myTarget->PAttack = NULL;
		DeleteInstance(this);
	}

	DrawBBox();
}
