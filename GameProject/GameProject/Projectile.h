#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "CollisionEntity.h"
#include "Enemy.h"

class Projectile : public CollisionEntity
{
public:
	Projectile(float aX, float aY, float aSpeed, float aDirection, bool aEnemyThreat, Enemy* aEnemy);
	~Projectile();

	void Update();

	void Draw();

private:
	bool myEnemyThreat;
	Enemy* myIgnorable;
};
#endif // !PROJECTILE_H