#include "stdafx.h"
#include "LaserEffect.h"


LaserEffect::LaserEffect(float aX, float aY, float aLength, float aDirection)
{
	Init("LaserEffect", aX, aY);

	float length = 0;
	
	for (int i = 0; i < aLength / 4; i++)
	{
		float lineLength = Math::IRand(30,60 );
		length += lineLength;
		
		if (length > aLength)
		{
			new LineEffect(myX, myY, length - aLength, aDirection, Math::Choose(true, false));
			break;
		}
		else
		{
			new LineEffect(myX, myY, lineLength + 30, aDirection, Math::Choose(true, false));
			myX += Math::LenDirX(lineLength - 5, Math::DegToRad(aDirection));
			myY += Math::LenDirY(lineLength - 5, Math::DegToRad(aDirection));
		}
	}

	DeleteInstance(this);
}


LaserEffect::~LaserEffect()
{
}
