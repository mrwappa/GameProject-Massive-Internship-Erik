#ifndef ENEMY_H
#define ENEMY_H

#include "CollisionEntity.h"

class PlayerAttack;
class Player;

class Enemy : public CollisionEntity
{
public:
	Enemy();
	~Enemy();
	void OnRemoval();

	virtual void StateIdle();
	virtual void StateAggro();
	virtual void StateAttack();
	virtual void StatePathFind();
	virtual void StateGrabbable();
	virtual void StateGrabbed();
	virtual void StateInUse();
	virtual void StateThrown();

	void Throw(float aSpeed, float aDir);

	void FindPath(float aX, float aY);

	static sf::Color GrabColor;
	static Player* Target;

	void SetState(int aState);
	
	int GetState() const;
	enum EnemyStates { Idle, Aggro, Attack, PathFind, Grabbable, Grabbed, InUse,Thrown};
	bool Alive() const;

protected:
	int myState;
	float myMoveSpeed;
	GrowingArray<AStarNode*> myPath;

	PlayerAttack* myAttackPtr;
};
#endif // !ENEMY_H
