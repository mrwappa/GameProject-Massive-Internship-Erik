#ifndef LASERENEMY_H
#define LASERENEMY_H

#include "Enemy.h"
#include "Player.h"

class LaserEnemy : public Enemy
{
public:
	LaserEnemy(float aX, float aY);
	~LaserEnemy();

	void Update();
};
#endif // !LASERENEMY_H