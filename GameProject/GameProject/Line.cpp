#include "stdafx.h"
#include "Line.h"


Line::Line()
{
	mySprite.SetTexture("Sprites/spr_pixel.png", 1);
}


Line::~Line()
{
}

void Line::DrawLinePos(float aX1, float aY1, float aX2, float aY2, float aDepth, sf::Color aColor)
{
	myDepth = aDepth;

	float deltax = aX2 - aX1;
	float deltay = aY2 - aY1;

	float deltalength = Math::SQRT2((deltax * deltax) + (deltay * deltay));

	mySprite.DrawOrigin(aX1, aY1, 0, 0, 1, deltalength, Math::RadToDeg(atan2f(deltay, deltax)) - 90 ,1, aColor, 0);
}