#ifndef GROUNDEDGE_H
#define GROUNDEDGE_H

#include "Brick.h"
#include "CollisionEntity.h"
class GroundEdge : public Solid
{
public:
	GroundEdge(float aX, float aY, int aBoxType);
	~GroundEdge();

	void Draw();
	
	enum BoxType{Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight};
};
#endif // !GROUNDEDGE_H
