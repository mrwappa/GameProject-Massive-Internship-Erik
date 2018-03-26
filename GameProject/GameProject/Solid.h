#ifndef SOLID_H
#define SOLID_H


#include "CollisionEntity.h"
class Solid : public CollisionEntity
{
public:

	void OnRemoval();
	Solid();
	~Solid();

};
#endif // !SOLID_H