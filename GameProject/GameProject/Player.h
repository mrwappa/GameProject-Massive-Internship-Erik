#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
class Player : Entity
{
public:
	Player(float aX, float aY, sf::Color aColor);
	~Player();

	void Update();
	void Draw();
};
#endif // !PLAYER_H