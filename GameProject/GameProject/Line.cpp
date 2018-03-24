#include "stdafx.h"
#include "Line.h"


Line::Line()
{
	Entity::Init("Line", 0, 0);
	mySprite.SetTexture("Sprites/spr_pixel.png", 1);
}


Line::~Line()
{
}

void Line::DrawLinePos(float aX1, float aY1, float aX2, float aY2, float aDepth, sf::Color aColor)
{
	float deltax = aX2 - aX1;
	float deltay = aY2 - aY1;

	float deltalength = Math::SQRT2((deltax * deltax) + (deltay * deltay));

	mySprite.DrawOrigin(aX1, aY1, 0, 0, 1, deltalength, Math::RadToDeg(atan2f(deltay, deltax)) - 90, aDepth, 1, aColor, 0);
}


