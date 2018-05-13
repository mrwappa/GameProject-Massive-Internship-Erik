#ifndef DASHENEMY_H
#define DASHENEMY_H

#include "Enemy.h"
#include "Player.h"

class DashEnemy : public Enemy
{
public:
	DashEnemy(float aX, float aY);
	~DashEnemy();

	void StateAggro();
	void StateAttack();
	void StateInUse();

	void Update();
	void EndUpdate();
	void Draw();

	Alarm AttackAlarm;
private:
	
	float myShake;

	bool myDash;
	bool myAccelerate;
};

#endif // !DASHENEMY_H