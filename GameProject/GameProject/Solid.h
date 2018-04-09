#ifndef SOLID_H
#define SOLID_H



#include "CollisionEntity.h"
class Solid : public CollisionEntity
{
public:

	Solid();
	~Solid();

	void Init(std::string aName, float aX, float aY);
	void OnRemoval();
	
protected:
	bool myCheckAdjacent;
};
#endif // !SOLID_H