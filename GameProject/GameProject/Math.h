#ifndef MATH_H
#define MATH_H

#define SQRT_MAGIC_F 0x5f3759df

class Math
{
public:
	Math();
	~Math();

	static const int Sign(float aX);
	static const float SQRT2(const float aX);
	static const float Clamp(float value, float min, float max);
};

#endif // !MATH_H