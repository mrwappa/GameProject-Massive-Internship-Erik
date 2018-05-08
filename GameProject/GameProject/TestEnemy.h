#ifndef TESTENEMY_H
#define TESTENEMY_H

#include "Enemy.h"
#include "Player.h"
#include "PlayerAttack.h"

class TestEnemy : public Enemy
{
public:

	TestEnemy(float aX, float aY);
	~TestEnemy();

	void StateAggro();
	void StateInUse();

	void Update();
	void Draw();
	void DrawGUI();

private:

	//For InUse State
	float myExtraX;
	float myExtraY;
	bool myRetract;

	GrowingArray<CollisionEntity*>* myEnemyTargets;
};
#endif // !TESTENEMY_H