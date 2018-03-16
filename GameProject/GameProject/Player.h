#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
class Player : Entity
{
public:
	Player(float aX, float aY);
	~Player();

	void Update();
	void Draw();
	void DrawGUI();

private:
	GSprite myGUISprite;

};
#endif // !PLAYER_H