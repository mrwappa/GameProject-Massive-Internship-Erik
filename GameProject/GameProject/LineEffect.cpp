#include "stdafx.h"
#include "LineEffect.h"


LineEffect::LineEffect(float aX, float aY, float aMaxLength, float aDirection, bool aFlipped)
{
	Init("LineEffect", aX, aY);

	myExtend = true;
	myLength = 0;
	myRetractSpeed = Math::FRand(0.2, 0.5);

	myMaxLength = aMaxLength;
	myAngle = aDirection;
	myFlipped = aFlipped;

	if (myFlipped)
	{
		myX += Math::LenDirX(myMaxLength, Math::DegToRad(myAngle));
		myY += Math::LenDirY(myMaxLength, Math::DegToRad(myAngle));
		myMaxLength = -myMaxLength;
	}

	myDepth = -9999;
}


LineEffect::~LineEffect()
{
}

void LineEffect::Update()
{
	if (myExtend)
	{
		myLength = Math::Lerp(myLength, myMaxLength, 0.7f);
		if (myLength > myMaxLength - 0.1f)
		{
			myExtend = false;
		}
	}
	else
	{
		myLength = Math::Lerp(myLength, 0, myRetractSpeed);
		if (myLength == 0)
		{
			DeleteInstance(this);
		}
	}
}

void LineEffect::Draw()
{
	DrawLine(myX, myY, myLength, myAngle, sf::Color::White);
}
