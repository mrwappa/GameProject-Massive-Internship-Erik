#ifndef PROJECTILEENEMY_H
#define PROJECTILEENEMY_H

#include "Enemy.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "Projectile.h"

class ProjectileEnemy : public Enemy
{
public:
	ProjectileEnemy(float aX, float aY);
	~ProjectileEnemy();

	void StateAggro();
	void StateAttack();
	void StateInUse();
	void StateGrabbed();

	void Update();

	void Draw();
	void DrawGUI();

private:

	float myAttackTimer;

	bool myDeflate;
};

#endif // !PROJECTILEENEMY_H