#ifndef MATH_H
#define MATH_H

#define SQRT_MAGIC_F 0x5f3759df
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include "GrowingArray.h"
#include <stdio.h>
#include <stdarg.h>

//Namespace didn't work, I have no idea why
class Math
{
public:
	Math();
	~Math();

	
	static const int Sign(float aX);
	static const float SQRT2(const float aX);
	static const float Clamp(float value, float min, float max);
	static float RadToDeg(float aRadians);
	static float DegToRad(float aDegrees);
	static float PointDirection(float aX1, float aY1, float aX2, float aY2);
	static float PointDirDeg(float aX1, float aY1, float aX2, float aY2);
	static float PointDistance(float aX1, float aY1, float aX2, float aY2);
	static float Lerp(float aStart, float aEnd, float aPercent);
	static float FRand(float aLow, float aHigh);
	static float IRand(float aLow, float aHigh);
	static float Decimal(float aX);
	static float SetDecimal(float aTarget, float aX);
	static float LenDirX(float aLength, float aDirection);
	static float LenDirY(float aLength, float aDirection);

	//Have to research more into parameter passing techniques and va_list
	//if I want to have unlimited parameters/arguments
	static float Choose(float aX, float aY);

};

#endif // !MATH_H