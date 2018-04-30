#include "stdafx.h"
#include "GroundEdge.h"


GroundEdge::GroundEdge(float aX, float aY, int aBoxType)
{
	Init("GroundEdge", aX, aY);

	myDepth = -myY + 100;

	myXScale = 2;
	myYScale = myXScale;

	if (aBoxType == Left)
	{
		myBoxHeight = 16;
		myBoxWidth = 2;
		myBoxXOffset = -16;
		myBoxYOffset = -10;
		mySprite.SetTexture(BRICKL, 1);
	}
	else if (aBoxType == Right)
	{
		myBoxHeight = 16;
		myBoxWidth = 2;
		myBoxXOffset = 16;
		myBoxYOffset = -10;
		mySprite.SetTexture(BRICKL, 1);
		myXScale = -2;
	}
	else if (aBoxType == Up)
	{
		myBoxWidth = 16;
		myBoxHeight = 2;
		myBoxYOffset = -16;
		mySprite.SetTexture(BRICKU, 1);
	}
	else if (aBoxType == Down)
	{
		myBoxWidth = 16;
		myBoxHeight = 2;
		myBoxYOffset = -3;
		mySprite.SetTexture(BRICKD, 1);
	}
	else if(aBoxType == DownRight)
	{
		myBoxWidth = 16;
		myBoxHeight = 2;
		myBoxYOffset = -3;
		mySprite.SetTexture(BRICKDL, 1);
		myXScale = -2;
	}
	else if (aBoxType == DownLeft)
	{
		myBoxWidth = 16;
		myBoxHeight = 2;
		myBoxYOffset = -3;
		mySprite.SetTexture(BRICKDL, 1);
	}
	else if (aBoxType == UpRight)
	{
		myBoxWidth = 16;
		myBoxHeight = 2;
		myBoxYOffset = -16;
		mySprite.SetTexture(BRICKUL, 1);
		myXScale = -2;
	}
	else if (aBoxType == UpLeft)
	{
		myBoxWidth = 16;
		myBoxHeight = 2;
		myBoxYOffset = -16;
		mySprite.SetTexture(BRICKUL, 1);
	}

	myActive = false;
}


GroundEdge::~GroundEdge()
{
}

void GroundEdge::Draw()
{
	Entity::Draw();
	//DrawBBox();
	//myColor = sf::Color::White;
}
