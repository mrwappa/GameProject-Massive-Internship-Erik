#ifndef MAGESPAWNER_H
#define MAGESPAWNER_H

#include "Enemy.h"
#include "Player.h"

class MageSpawner : public Enemy
{
public:
	MageSpawner(float aX, float aY);
	~MageSpawner();

	void StateAggro();
	void StateGrabbed();
	void StateFallInAbyss();
	void StateAttack();

	void Update();
	void Draw();

private:
	Alarm mySpawnAlarm;
	Alarm myAttackAlarm;
};
#endif // !MAGESPAWNER_H