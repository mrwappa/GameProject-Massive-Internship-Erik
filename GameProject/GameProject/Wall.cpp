#include "stdafx.h"
#include "Wall.h"


Wall::Wall(float aX, float aY)
{
	Init("Wall", aX, aY);

	myBoxWidth = 14;
	myBoxHeight = 16;
	myXScale = 2;
	myYScale = 2;
	myDepth = myY - 20;

	myCheckAdjacent = true;
}


Wall::~Wall()
{
}

void Wall::Update()
{
	if (myCheckAdjacent)
	{
		bool wallD = ObjPosition(myX, myY + 32, "Wall");
		bool wallL = ObjPosition(myX - 32, myY, "Wall");
		bool wallR = ObjPosition(myX + 32, myY, "Wall");
		
		if (wallD and wallL and wallR)
		{
			mySprite.SetTexture(WALLM, 1);
		}
		if (wallD and !wallL  and wallR)
		{
			mySprite.SetTexture(WALLL, 1);
		}
		if (!wallD and !wallL and wallR)
		{
			myBoxHeight = 8;
			myBoxYOffset = -8;
			mySprite.SetTexture(WALLDL, 1);
		}
		if (!wallD and wallL and wallR)
		{
			myBoxHeight = 8;
			myBoxYOffset = -8;
			mySprite.SetTexture(WALLMD, 1);
		}
		if (!wallD and !wallL and !wallR)
		{
			myBoxHeight = 8;
			myBoxYOffset = -8;
			mySprite.SetTexture(WALLMM, 1);
		}
		if (wallD and wallL and !wallR)
		{
			mySprite.SetTexture(WALLR, 1);
		}
		if (!wallD and wallL and !wallR)
		{
			myBoxHeight = 8;
			myBoxYOffset = -8;
			mySprite.SetTexture(WALLRD, 1);
		}
		
		myCheckAdjacent = false;
	}
}

void Wall::Draw()
{
	Entity::Draw();
	//DrawBBox();
}
