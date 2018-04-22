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
	void Init(std::string aName, float aX, float aY);

	void OnRemoval();

	virtual void StateIdle();
	virtual void StateSpawned();
	virtual void StateAggro();
	virtual void StateAttack();
	virtual void StatePathFind();
	virtual void StateGrabbable();
	virtual void StateGrabbed();
	virtual void StateInUse();
	virtual void StateThrown();
	virtual void StateFallInAbyss();

	void BeginUpdate();
	void Update();
	void EndUpdate();

	void Throw(float aSpeed, float aDir);
	void Fall();

	void FindPath(float aX, float aY);

	void DrawShadow(float aX, float aY, float aXScale, float aYScale);
	
	static sf::Color GrabColor;
	static Player* Target;

	void SetState(int aState);
	void SetPrevState(int aState);
	void SetZ(float aZ);

	int GetState() const;
	enum EnemyStates { Spawned ,Idle, Aggro, Attack, PathFind, Grabbable, Grabbed, InUse, Thrown, FallInAbyss};
	bool Alive() const;

protected:

	int myState;
	int myPrevState;
	float myZSpeed;
	float myZTarget;
	float myPrevHP;

	Alarm myThrowAlarm;

	GrowingArray<AStarNode*> myPath;

	PlayerAttack* myAttackPtr;

	GSprite myShadow;

private:
	Vector2f myWalkPoint;
	Alarm myWalkAlarm;

	float mySpawnSpeed;

	bool myJustThrown;
	Alarm myHurtAlarm;
};
#endif // !ENEMY_H
