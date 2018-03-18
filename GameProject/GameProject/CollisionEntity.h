#ifndef COLLISION_ENTITY
#define COLLISION_ENTITY

#include "Entity.h"

class CollisionEntity : public Entity
{
public:
	CollisionEntity();
	~CollisionEntity();



protected:
	float myMovementSpeed;
	float myXSpeed;
	float myYSpeed;
};

#endif // !COLLISION_ENTITY