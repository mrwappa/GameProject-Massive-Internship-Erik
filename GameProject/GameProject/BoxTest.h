#ifndef BOXTEST_H
#define BOXTEST_H

#include "CollisionEntity.h"

class BoxTest : public CollisionEntity
{
public:
	BoxTest(float aX, float aY, bool aUnique);
	~BoxTest();

	void Update();
	void Draw();

private:
	bool myUnique;
};
#endif // !DEFINE_H