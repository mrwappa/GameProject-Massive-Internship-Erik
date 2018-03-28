#ifndef SOLID_H
#define SOLID_H


#include "CollisionEntity.h"
class Solid : public CollisionEntity
{
public:

	Solid();
	~Solid();
	void OnRemoval();
};
#endif // !SOLID_H