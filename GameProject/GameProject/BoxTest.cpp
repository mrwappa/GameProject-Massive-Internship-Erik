#include "stdafx.h"
#include "BoxTest.h"


BoxTest::BoxTest(float aX, float aY, bool aUnique)
{
	Init("BoxTest", aX, aY);
	mySprite.SetTexture("Sprites/32x32Block.png", 1);

	myBoxWidth = 32;
	myBoxHeight = 32;

	myUnique = aUnique;
}


BoxTest::~BoxTest()
{
}

void BoxTest::Update()
{
	myDepth = myY;
	CollisionEntity* box = ObjCollision(myX, myY, "BoxTest");

	myColor = sf::Color::Green;
	if (box != NULL)
	{
		myColor = sf::Color::Red;
	}

	if (myUnique)
	{
		if (KeyboardCheck(sf::Keyboard::I))
		{
			myAngle += 1.5f;
		}
		if (KeyboardCheck(sf::Keyboard::K))
		{
			myAngle -= 1.5f;
		}

		if (KeyboardCheck(sf::Keyboard::Num8))
		{
			myZ += 2;
		}
		if (KeyboardCheck(sf::Keyboard::Num7))
		{
			myZ -= 2;
		}
		if (KeyboardCheck(sf::Keyboard::U))
		{
			myXScale += 0.05f;
			myYScale = myXScale;
		}
		if (KeyboardCheck(sf::Keyboard::J))
		{
			myXScale -= 0.05f;
			myYScale = myXScale;
		}

		if (MouseCheck(sf::Mouse::Left))
		{
			myX = Camera->GetMouseX();
			myY = Camera->GetMouseY();
		}
	}
	else
	{
		if (KeyboardCheck(sf::Keyboard::O))
		{
			myAngle += 1.5f;
		}
		if (KeyboardCheck(sf::Keyboard::L))
		{
			myAngle -= 1.5f;
		}

		if (KeyboardCheck(sf::Keyboard::Num9))
		{
			myZ += 2;
		}
		if (KeyboardCheck(sf::Keyboard::Num0))
		{
			myZ -= 2;
		}
		if (KeyboardCheck(sf::Keyboard::Subtract))
		{
			myXScale += 0.05f;
			myYScale = myXScale;
		}
		if (KeyboardCheck(sf::Keyboard::Add))
		{
			myXScale -= 0.05f;
			myYScale = myXScale;
		}

		if (MouseCheck(sf::Mouse::Right))
		{
			myX = Camera->GetMouseX();
			myY = Camera->GetMouseY();
		}
	}
}

void BoxTest::Draw()
{
	Entity::Draw();
	DrawBBox();
}
