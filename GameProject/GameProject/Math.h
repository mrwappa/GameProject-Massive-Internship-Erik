#ifndef MATH_H
#define MATH_H

#define SQRT_MAGIC_F 0x5f3759df
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

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
	static float PointDirection(float aX1, float aY1, float aX2, float aY2);
	static float Lerp(float aStart, float aEnd, float aPercent);
	static float FRand(float aLow, float aHigh);
	static float IRand(float aLow, float aHigh);

};

#endif // !MATH_H