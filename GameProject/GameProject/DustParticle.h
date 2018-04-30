#ifndef DUSTPARICLE_H
#define DUSTPARICLE_H

#include "CollisionEntity.h"

class DustParticle : public CollisionEntity
{
public:
	DustParticle(float aX, float aY ,sf::Color aColor);
	~DustParticle();

	void Update();
	void Fall();

private:
	float myZSpeed;
	Alarm myDestroyAlarm;
};
#endif // !DUSTPARICLE_H