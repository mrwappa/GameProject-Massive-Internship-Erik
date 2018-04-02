#include "stdafx.h"
#include "Brick.h"

Brick::Brick(float aX, float aY)
{
	Init("Brick",aX,aY);
	mySprite.SetTexture("Sprites/32x32Block.png", 1);

	myBoxWidth = 32;
	myBoxHeight = 32;
	myDepth = -myY;
}


Brick::~Brick()
{

}

void Brick::Update()
{
	if (KeyboardCheckPressed(sf::Keyboard::Tab))
	{
		DeleteInstance(this);
	}
}

void Brick::Draw()
{
	Entity::Draw();
	DrawBBox();
}