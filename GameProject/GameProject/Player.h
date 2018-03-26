#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "CollisionEntity.h"
#include "Math.h"
#include "Line.h"
class Player : public CollisionEntity
{
public:
	Player(float aX, float aY);
	~Player();

	void Update();
	void Draw();
	void DrawGUI();

private:
	bool W;
	bool A;
	bool S;
	bool D;

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

	sf::Texture myCharTextures[5];

	enum CharTexture {Back, BackLeft, Front, FrontLeft,Left};
	
};
#endif // !PLAYER_H