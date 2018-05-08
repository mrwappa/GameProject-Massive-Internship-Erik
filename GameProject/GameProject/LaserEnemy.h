#ifndef LASERENEMY_H
#define LASERENEMY_H

#include "Enemy.h"
#include "Player.h"

class LaserEnemy : public Enemy
{
public:
	LaserEnemy(float aX, float aY);
	~LaserEnemy();

	void StateAttack();
	void StateAggro();
	void StateInUse();
	void StateGrabbed();

	void Update();
	void Draw();

private:
	Alarm myAttackAlarm;

	
};
#endif // !LASERENEMY_H