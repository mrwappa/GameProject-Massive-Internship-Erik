#ifndef LINEEFFECT_H
#define LINEEFFECT_H

#include "Entity.h"

class LineEffect : public Entity
{
public:
	LineEffect(float aX, float aY, float aMaxLength, float aDirection, bool aFlipped);
	~LineEffect();

	void Update();
	void Draw();
private:
	float myMaxLength;
	float myLength;
	float myRetractSpeed;

	bool myExtend;
	bool myFlipped;
};
#endif // !LINEEFFECT_H