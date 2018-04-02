#ifndef ENEMY_H
#define ENEMY_H

#include "CollisionEntity.h"

class Player;

class Enemy : public CollisionEntity
{
public:
	Enemy();
	~Enemy();
	void OnRemoval();

	virtual void StateIdle();
	virtual void StateAggro();
	virtual void StatePathFind();

	static Player* Target;

protected:
	int myState;
	enum EnemyStates { Idle, Aggro, PathFind, Grabbable, Grabbed, InUse };
	float myDirection;
};
#endif // !ENEMY_H
