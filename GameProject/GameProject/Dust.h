#ifndef DUST_H
#define DUST_H

#include "Entity.h"

class Dust : public Entity
{
public:
	Dust(float aX, float aY, float aAngle);
	~Dust();

	void Update();
};

#endif // !DUST_H