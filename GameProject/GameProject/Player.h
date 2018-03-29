#ifndef PLAYER_H
#define PLAYER_H

#include "CollisionEntity.h"
#include "Math.h"
#include "Line.h"
#include "Dust.h"
#include "Enemy.h"

class PlayerAttack;

class Player : public CollisionEntity
{
public:
	Player(float aX, float aY);
	~Player();

	void Update();
	void BeginUpdate();
	void Draw();
	void DrawGUI();

	void OnRemoval();

	PlayerAttack* PAttack;

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

	float myLookAngle;
	
	float myAttackTimer;

	void TextureDirection(float aAngle);
	//if these textures are not created and deleted on the heap, I get a memory leak
	//thanks SFML...
	sf::Texture* myCharTextures[5];
	
	enum CharTexture {Back, BackLeft, Front, FrontLeft,Left, T_SIZE};

	GSprite* myShadow;
};
#endif // !PLAYER_H