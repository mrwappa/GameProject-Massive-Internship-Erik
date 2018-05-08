#ifndef MAGESPAWNER_H
#define MAGESPAWNER_H

#include "Enemy.h"
#include "Player.h"
#include "ProjectileEnemy.h"
#include "TestEnemy.h"
#include "LaserEnemy.h"

class MageSpawner : public Enemy
{
public:
	MageSpawner(float aX, float aY);
	~MageSpawner();

	void StateAggro();
	void StateGrabbed();
	void StateGrabbable();
	void StateFallInAbyss();
	void StateAttack();
	void StateInUse();
	

	void SpawnEnemy();

	void Update();
	void Draw();

private:
	Alarm mySpawnAlarm;
	Alarm myAttackAlarm;

	float myShake;

	enum Enemies{Projectile, Fly, Laser, ENEMIES_SIZE};
};
#endif // !MAGESPAWNER_H