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
	virtual void StateGrabbable();
	virtual void StateGrabbed();
	virtual void StateInUse();
	
	static sf::Color GrabColor;
	static Player* Target;

	void SetState(int aState);
	
	int GetState() const;
	enum EnemyStates { Idle, Aggro, PathFind, Grabbable, Grabbed, InUse };

protected:
	int myState;
	float myDirection;
};
#endif // !ENEMY_H
