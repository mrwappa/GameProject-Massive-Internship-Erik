#ifndef TESTENEMY_H
#define TESTENEMY_H

#include "Enemy.h"
#include "Player.h"

class TestEnemy : public Enemy
{
public:
	TestEnemy(float aX, float aY);
	~TestEnemy();

	void Update();
	void Draw();

private:
	CollisionEntity* myAttackPtr;
};
#endif // !TESTENEMY_H