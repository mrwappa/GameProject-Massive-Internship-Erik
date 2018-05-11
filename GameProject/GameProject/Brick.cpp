#include "stdafx.h"
#include "Brick.h"

Brick::Brick(float aX, float aY)
{
	Init("Brick",aX,aY);

	myBoxWidth = 14;
	myBoxHeight = 16;
	myXScale = 2;
	myYScale = 2;
	myDepth = -myY;
}


Brick::~Brick()
{

}

void Brick::Update()
{
	//Instead of this I could check the AStarGrid for adjacent nodes if they are walkable or not(should be faster)
	//Realizing it probably won't work because there's a difference between Wall and Brick.
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
		myBoxHeight = 8;
		myBoxYOffset = 8;
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
		myBoxHeight = 8;
		myBoxYOffset = 8;
		mySprite.SetTexture(BRICKU, 1);
	}
	if (!brickU and !brickD and brickL and brickR)
	{
		myBoxHeight = 8;
		myBoxYOffset = 8;
		mySprite.SetTexture(BRICKUD, 1);
	}
	if (!brickU and !brickD and !brickL and brickR)
	{
		myBoxHeight = 8;
		myBoxYOffset = 8;
		mySprite.SetTexture(BRICKUDL, 1);
	}
	if (!brickU and !brickD and brickL and !brickR)
	{
		myBoxHeight = 8;
		myBoxYOffset = 8;
		mySprite.SetTexture(BRICKUDL, 1);
		myXScale = -2;
	}
	if (!brickU and brickD and !brickL and brickR)
	{
		myBoxHeight = 8;
		myBoxYOffset = 8;
		mySprite.SetTexture(BRICKUL, 1);
	}
	if (!brickU and brickD and brickL and !brickR)
	{
		myBoxHeight = 8;
		myBoxYOffset = 8;
		mySprite.SetTexture(BRICKUL, 1);
		myXScale = -2;
	}
	if (brickU and !brickD and !brickL and !brickR)
	{
		mySprite.SetTexture(BRICKDLR, 1);
	}
	if (!brickU and brickD and !brickL and !brickR)
	{
		myBoxHeight = 8;
		myBoxYOffset = 8;
		mySprite.SetTexture(BRICKULR, 1);
	}

	myActive = false;
	myOutOfLoop = true;
}

void Brick::Draw()
{
	Entity::Draw();
	//DrawBBox();
}