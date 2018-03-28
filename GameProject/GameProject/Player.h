#ifndef PLAYER_H
#define PLAYER_H

#include "CollisionEntity.h"
#include "Math.h"
#include "Line.h"
#include "Dust.h"
#include "Enemy.h"

class Player : public CollisionEntity
{
public:
	Player(float aX, float aY);
	~Player();

	void Update();
	void Draw();
	void DrawGUI();

	void OnRemoval();

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

	void TextureDirection(float aAngle);
	//if these textures are not created and deleted on the heap, I get a memory leak
	//thanks SFML...
	sf::Texture* myCharTextures[5];
	
	enum CharTexture {Back, BackLeft, Front, FrontLeft,Left, T_SIZE};

	//this is the most odd and stupid thing I've ever come across.
	//Declaring a Texture pointer makes any object that inherits from 
	//Entity Removed from the main update loop entirely. But if I make it into an array
	//it thinks that it's totally fine...
	GSprite* myShadow[1];
};
#endif // !PLAYER_H