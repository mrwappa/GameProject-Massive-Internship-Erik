#ifndef TESTENEMY_H
#define TESTENEMY_H

#include "Enemy.h"
#include "Player.h"
#include "Line.h"
#include "PlayerAttack.h"

class TestEnemy : public Enemy
{
public:
	TestEnemy(float aX, float aY);
	~TestEnemy();

	void FindPath(float aX, float aY);

	void StateAggro();
	void StatePathFind();
	void StateIdle();
	void StateGrabbable();
	void StateGrabbed();

	void Update();
	void Draw();
	void DrawGUI();
	
	void OnRemoval();

private:
	PlayerAttack* myAttackPtr;

	GrowingArray<AStarNode*> myPath;
	int myPrevState;

	Line myLine;
};
#endif // !TESTENEMY_H