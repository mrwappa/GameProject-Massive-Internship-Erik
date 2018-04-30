#include "stdafx.h"
#include "Ground.h"


Ground::Ground(float aX, float aY)
{
	Init("Ground", aX, aY);

	mySprite.SetTexture("Sprites/Blocks/spr_grassBLANK.png", 1);
	myXScale = 2;
	myYScale = myXScale;

	myDepth = -myY + 100;

	myActive = false;
}


Ground::~Ground()
{
}

