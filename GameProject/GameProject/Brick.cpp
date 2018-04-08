#include "stdafx.h"
#include "Brick.h"

Brick::Brick(float aX, float aY)
{
	Init("Brick",aX,aY);
	//mySprite.SetTexture("Sprites/32x32Block.png", 1);

	myBoxWidth = 16;
	myBoxHeight = 16;
	myXScale = 2;
	myYScale = 2;
	myDepth = myY;

	myCheckAdjacent = true;
}


Brick::~Brick()
{

}

void Brick::Update()
{
	if (myCheckAdjacent)
	{
		bool brickU = ObjPosition(myX, myY - 32,"Brick");
		bool brickD = ObjPosition(myX, myY + 32, "Brick");
		bool brickL = ObjPosition(myX - 32, myY, "Brick");
		bool brickR = ObjPosition(myX + 32, myY, "Brick");

		if (brickU and brickD and brickL and brickR)
		{
			mySprite.SetTexture(BRICKBLANK, 1);
		}
		if (brickU and !brickD and brickL and brickR)
		{
			mySprite.SetTexture(BRICKD, 1);
		}
		if (brickU and !brickD and !brickL and brickR)
		{
			mySprite.SetTexture(BRICKDL, 1);
		}
		if (brickU and !brickD and brickL and !brickR)
		{
			mySprite.SetTexture(BRICKDL, 1);
			myXScale = -2;
		}
		if (!brickU and !brickD and !brickL and !brickR)
		{
			mySprite.SetTexture(BRICKFILLED, 1);
		}
		if (brickU and brickD and !brickL and brickR)
		{
			mySprite.SetTexture(BRICKL, 1);
		}
		if (brickU and brickD and !brickL and !brickR)
		{
			mySprite.SetTexture(BRICKLR, 1);
		}
		if (brickU and brickD and brickL and !brickR)
		{
			mySprite.SetTexture(BRICKL, 1);
			myXScale = -2;
		}
		if (!brickU and brickD and brickL and brickR)
		{
			mySprite.SetTexture(BRICKU, 1);
		}
		if (!brickU and !brickD and brickL and brickR)
		{
			mySprite.SetTexture(BRICKUD, 1);
		}
		if (!brickU and !brickD and !brickL and brickR)
		{
			mySprite.SetTexture(BRICKUDL, 1);
		}
		if (!brickU and !brickD and brickL and !brickR)
		{
			mySprite.SetTexture(BRICKUDL, 1);
			myXScale = -2;
		}
		if (!brickU and brickD and !brickL and brickR)
		{
			mySprite.SetTexture(BRICKUL, 1);
		}
		if (!brickU and brickD and brickL and !brickR)
		{
			mySprite.SetTexture(BRICKUL, 1);
			myXScale = -2;
		}
		/*if (brickU and !brickD and !brickL and !brickR)
		{
			mySprite.SetTexture(BRICKUL, 1);
			myXScale = -2;
		}*/
		if (brickU and !brickD and !brickL and !brickR)
		{
			mySprite.SetTexture(BRICKDLR, 1);
		}
		if (!brickU and brickD and !brickL and !brickR)
		{
			mySprite.SetTexture(BRICKULR, 1);
		}

		//myCheckAdjacent = false;
	}
}

void Brick::Draw()
{
	Entity::Draw();
	DrawBBox();
}