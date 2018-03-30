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

	void FindPath();
	void Update();
	void Draw();

	void OnRemoval();

private:
	CollisionEntity* myAttackPtr;

	Line myLine;

	int myPrevState;
	GrowingArray<Vector2f> myPath;
};
#endif // !TESTENEMY_H