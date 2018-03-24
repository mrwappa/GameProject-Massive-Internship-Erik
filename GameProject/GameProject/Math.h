#ifndef MATH_H
#define MATH_H

#define SQRT_MAGIC_F 0x5f3759df
#define _USE_MATH_DEFINES
#include <math.h>

class Math
{
public:
	Math();
	~Math();

	//Namespace didn't work, have no idea why
	static const int Sign(float aX);
	static const float SQRT2(const float aX);
	static const float Clamp(float value, float min, float max);
	static float RadToDeg(float aRadians);
	static float DegToRad(float aDegrees);
	static float darctan2(float aX, float aY);
};

#endif // !MATH_H