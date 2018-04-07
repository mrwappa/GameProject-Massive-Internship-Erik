#ifndef PLAYERATTACK_H
#define PLAYERATTACK_H

#include "CollisionEntity.h"
#include "Player.h"

class PlayerAttack : public CollisionEntity
{
public:
	PlayerAttack(float aX, float aY, Player* aTarget);
	~PlayerAttack();

	void Update();
	void Draw();

private:
	Player* myTarget;

};
#endif // !PLAYERATTACK_H