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

	void StateAggro();
	void StateInUse();

	void Update();
	void Draw();
	void DrawGUI();

private:
	int myPrevState;

	//For InUse State
	float myExtraX;
	float myExtraY;
	bool myRetract;

	Line myLine;
};
#endif // !TESTENEMY_H