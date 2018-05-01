#ifndef LASERPROJECTILE_H
#define LASERPROJECTILE_H

#include "Enemy.h"


class LaserProjectile : public CollisionEntity
{
public:
	LaserProjectile(float aX, float aY,  float aAngle, bool aEnemyThreat);
	~LaserProjectile();

	void Update();
	void Draw();

private:
	bool myEnemyThreat;
	float myLength;
	Vector2f myTargetPosition;

};

#endif // !LASERPROJECTILE_H