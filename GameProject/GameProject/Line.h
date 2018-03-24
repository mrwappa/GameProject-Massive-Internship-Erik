#ifndef LINE_H
#define LINE_H

#include "Entity.h"
#include "Math.h"

class Line : public Entity
{
public:
	Line();
	~Line();

	void DrawLinePos(float aX1, float aY1, float aX2, float aY2, float aDepth,  sf::Color aColor);
};

#endif // !LINE_H