#include "stdafx.h"
#include "Brick.h"

Brick::Brick(float aX, float aY)
{
	Entity::Init("Brick",aX,aY);
	mySprite.SetTexture("Sprites/32x32Block.png", 1);

	myBoxWidth = 32;
	myBoxHeight = 32;
}


Brick::~Brick()
{
}

void Brick::Update()
{
	myDepth = -myY;
}

void Brick::Draw()
{
	Entity::Draw();
	DrawBBox();
}
