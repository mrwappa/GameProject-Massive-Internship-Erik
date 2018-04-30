#include "stdafx.h"
#include "DustParticle.h"


DustParticle::DustParticle(float aX, float aY, sf::Color aColor)
{
	Init("DustParticle", aX, aY);
	mySprite.SetTexture("Sprites/spr_pixel.png", 1);

	myColor = aColor;

	myDestroyAlarm.SetTick(Math::IRand(120, 240));

	myXScale = Math::FRand(1.8f,2.5f);
	myYScale = myXScale;
	myXSpeed = Math::FRand(-2.8f, 2.8f);
	myYSpeed = Math::FRand(-2.8f, 2.8f);
	myZSpeed = Math::FRand(0.7,2);
	myZ = Math::IRand(10, 25);
}


DustParticle::~DustParticle()
{
}

void DustParticle::Update()
{

	myDepth = -myY + myZ + 25;
	Fall();

	Move(myXSpeed, myYSpeed);
	myXSpeed = Math::Lerp(myXSpeed, 0, 0.18f);
	myYSpeed = Math::Lerp(myYSpeed, 0, 0.18f);

	if (myDestroyAlarm.GetTick() == -1)
	{
		DeleteInstance(this);
	}
}

void DustParticle::Fall()
{
	myZSpeed -= 0.35f;
	if ((myZ + myZSpeed) < 0)
	{
		while (myZ + Math::Sign(myZSpeed) > 0)
		{
			myZ += Math::Sign(myZSpeed);
		}
		if (abs(myZSpeed) > 1.5f)
		{
			myZSpeed *= -0.74f;
		}
		else
		{
			myZSpeed = 0;
		}
	}
	else
	{
		myZ += myZSpeed;
	}
}
