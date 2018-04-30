#include "stdafx.h"
#include "GroundPillar.h"


GroundPillar::GroundPillar(float aX, float aY, int aPillar)
{
	Init("GroundPillar", aX, aY);

	if (aPillar == Left)
	{
		mySprite.SetTexture(PILLARL, 1);
	}
	else if (aPillar == Right)
	{
		mySprite.SetTexture(PILLARR, 1);
	}
	else if (aPillar == Middle)
	{
		mySprite.SetTexture(PILLARM, 1);
	}
	
	myXScale = 2;
	myYScale = myXScale;

	myDepth = -myY + 100;

	myActive = false;
}


GroundPillar::~GroundPillar()
{
}
