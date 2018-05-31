#ifndef PLAYERATTACK_H
#define PLAYERATTACK_H

#include "CollisionEntity.h"
#include "Player.h"
#include "Enemy.h"

class PlayerAttack : public CollisionEntity
{
public:
	PlayerAttack(float aX, float aY);
	~PlayerAttack();

	void Update();
	void Draw();



};
#endif // !PLAYERATTACK_H