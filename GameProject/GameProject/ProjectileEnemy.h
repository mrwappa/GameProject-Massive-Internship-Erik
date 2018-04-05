#ifndef PROJECTILEENEMY_H
#define PROJECTILEENEMY_H

#include "Enemy.h"
#include "Line.h"
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

	void Update();

	void Draw();
	void DrawGUI();

private:

	Line myLine;

	float myAttackTimer;
};

#endif // !PROJECTILEENEMY_H