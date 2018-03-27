#ifndef BRICK_H
#define BRICK_H

#include "Solid.h"

class Brick : public Solid
{
public:
	Brick(float aX, float aY);
	~Brick();

	void Update();
	void Draw();


};

#endif // !BRICK_H