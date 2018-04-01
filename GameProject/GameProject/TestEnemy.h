#ifndef TESTENEMY_H
#define TESTENEMY_H

#include "Enemy.h"
#include "Player.h"
#include "Line.h"


class TestEnemy : public Enemy
{
public:
	TestEnemy(float aX, float aY);
	~TestEnemy();

	void FindPath(float aX, float aY);
	void Update();
	void Draw();

	void OnRemoval();

private:
	CollisionEntity* myAttackPtr;

	GrowingArray<AStarNode*> myPath;
	int myPrevState;
};
#endif // !TESTENEMY_H