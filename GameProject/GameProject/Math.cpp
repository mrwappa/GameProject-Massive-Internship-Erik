#include "stdafx.h"
#include "Math.h"



Math::Math()
{
}



Math::~Math()
{
}

const int Math::Sign(float aX)
{
	return aX < 0 ? -1 : aX == 0 ? 0 : 1;
}


const float Math::SQRT2(const float aX)
{
	const float xhalf = 0.5f*aX;

	union // get bits for floating value
	{
		float x;
		int i;
	} u;

	u.x = aX;
	u.i = SQRT_MAGIC_F - (u.i >> 1);  // gives initial guess y0

	return aX * u.x*(1.5f - xhalf * u.x*u.x); // Newton step, repeating increases accuracy 
}

const float Math::Clamp(float value, float min, float max)
{
	return value <= min ? min : value >= max ? max : value;
}

float Math::RadToDeg(float aRadians)
{
	return aRadians * (180 * M_PI);
}

float Math::DegToRad(float aDegrees)
{
	return aDegrees / (180 / M_PI);
}
