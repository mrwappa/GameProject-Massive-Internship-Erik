#ifndef BRICK_H
#define BRICK_H

#include "CollisionEntity.h"

class Brick : public CollisionEntity
{
public:
	Brick(float aX, float aY);
	~Brick();

	void Update();
	void Draw();

};

#endif // !BRICK_H