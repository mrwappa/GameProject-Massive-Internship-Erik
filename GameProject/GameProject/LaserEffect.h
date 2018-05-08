#ifndef LASEREFFECT_H
#define LASEREFFECT_H


#include "LineEffect.h"

class LaserEffect : public Entity
{
public:
	LaserEffect(float aX, float aY, float aLength, float aDirection);
	~LaserEffect();

};
#endif // !LASEREFFECT_H