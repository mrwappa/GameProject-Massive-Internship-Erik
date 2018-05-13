#ifndef PLAYER_H
#define PLAYER_H

#include "CollisionEntity.h"
#include "Math.h"
#include "Dust.h"
#include "Enemy.h"
#include "Projectile.h"
#include "LaserProjectile.h"
#include "LaserEffect.h"

class PlayerAttack;

class Player : public CollisionEntity
{
public:
	Player(float aX, float aY);
	~Player();

	void Update();
	void BeginUpdate();
	void EndUpdate();

	void Draw();
	void DrawGUI();

	void OnRemoval();
	void Hurt(float aDamage,float aDirection);

	Enemy* NearestGrabbable();

	PlayerAttack* PAttack;
	Enemy* GrabbableEnemy;

	enum PlayerStates { Normal, Dash };
	int GetState() const;

private:
	bool W;
	bool A;
	bool S;
	bool D;

	int myPreviousAIndex;

	float myXAcceleration;
	float myYAcceleration;
	float myYRestitution;
	float myXRestitution;
	
	float myXSpeedMax;
	float myYSpeedMax;
	int myXDir;
	int myYDir;
	float myXAdd;
	float myYAdd;
	float myXSub;
	float myYSub;

	float myDirection;

	
	int myState;
	bool myAccelerate;

	void StateNormal();
	void StateDash();

	Alarm myHurtAlarm;
	Alarm myInvisAlarm;
	float myAttackTimer;

	void TextureDirection(float aAngle);
	std::string myCharTextures[5];
	enum CharTexture {Back, BackLeft, Front, FrontLeft ,Left, T_SIZE};

	GSprite myShadow;
};
#endif // !PLAYER_H