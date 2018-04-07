#include "stdafx.h"
#include "Dust.h"


Dust::Dust(float aX, float aY, float aAngle)
{
	Init("Dust", aX, aY);
	mySprite.SetTexture("Sprites/Player/spr_dust.png",7);
	myAngle = aAngle;
	myDepth = -myY - 50;
	myAlpha = 0.27f;
	myAnimationSpeed = 0.2f;
}


Dust::~Dust()
{
}

void Dust::Update()
{
	if (mySprite.GetAnimationIndex() == mySprite.GetNrOfFrames() - 1)
	{
		DeleteInstance(this);
	}
}