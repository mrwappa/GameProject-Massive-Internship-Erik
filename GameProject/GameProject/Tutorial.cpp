#include "stdafx.h"
#include "Tutorial.h"


Tutorial::Tutorial()
{
	Init("Tutorial", -1000, -1000);
	for (int i = 0; i < 4; i++)
	{
		myWalk[i] = false;
	}
	for (int i = 0; i < 2; i++)
	{
		myUseEnemy[i] = false;
	}
}


Tutorial::~Tutorial()
{
}

void Tutorial::Update()
{
	
}

void Tutorial::DrawGUI()
{
	if (myState == Walk)
	{
		if (KeyboardCheckPressed(sf::Keyboard::W))
		{
			myWalk[0] = true;
		}
		if (KeyboardCheckPressed(sf::Keyboard::A))
		{
			myWalk[1] = true;
		}
		if (KeyboardCheckPressed(sf::Keyboard::S))
		{
			myWalk[2] = true;
		}
		if (KeyboardCheckPressed(sf::Keyboard::D))
		{
			myWalk[3] = true;
		}

		int nrOfPressed = 0;
		for (int i = 0; i < 4; i++)
		{
			if (myWalk[i] == true)
			{
				nrOfPressed++;
			}
		}
		if (nrOfPressed >= 3)
		{
			myState = Attack;
		}

		DrawFontGUI("Walk With:", 100, 100, 24, 1, 1, sf::Color::White);
		DrawFontGUI("W", 180, 140, 24, 1, 1, sf::Color::Red);
		DrawFontGUI("A", 160, 165, 24, 1, 1, sf::Color::Red);
		DrawFontGUI("S", 180, 165, 24, 1, 1, sf::Color::Red);
		DrawFontGUI("D", 200, 165, 24, 1, 1, sf::Color::Red);
	}
	if (myState == Attack)
	{
		if (MouseCheckPressed(sf::Mouse::Left))
		{
			myState = Pickup;
		}
		DrawFontGUI("Attack With:", 100, 100, 24, 1, 1, sf::Color::White);
		DrawFontGUI("Left Mouse Button", 100, 130, 24, 1, 1, sf::Color::Red);
	}
	if (myState == Pickup)
	{
		DrawFontGUI("Press", 100, 130, 24, 1, 1, sf::Color::White);
		DrawFontGUI("SHIFT", 200, 130, 24, 1, 1, sf::Color::Red);
		DrawFontGUI("to pick up Defeated Enemy", 290, 130, 24, 1, 1, sf::Color::White);

		if (Enemy::Target->GrabbableEnemy != NULL)
		{
			myState = UseEnemy;
		}
	}
	if (myState == UseEnemy)
	{
		if (Enemy::Target->GrabbableEnemy != NULL)
		{
			if (MouseCheckPressed(sf::Mouse::Left))
			{
				myUseEnemy[0] = true;
			}
		}

		if (KeyboardCheckPressed(sf::Keyboard::Space))
		{
			myUseEnemy[1] = true;
		}

		if (myUseEnemy[0] == true and myUseEnemy[1] == true)
		{
			myState = NextLevel;
		}

		DrawFontGUI("Press", 100, 130, 24, 1, 1, sf::Color::White);
		DrawFontGUI("Left Mouse Button", 200, 130, 24, 1, 1, sf::Color::Red);
		DrawFontGUI("to use Enemy", 540, 130, 24, 1, 1, sf::Color::White);

		DrawFontGUI("Press", 100, 150, 24, 1, 1, sf::Color::White);
		DrawFontGUI("SPACE", 200, 150, 24, 1, 1, sf::Color::Red);
		DrawFontGUI("to throw Enemy", 290, 150, 24, 1, 1, sf::Color::White);


	}
	if (myState == NextLevel)
	{
		DrawFontGUI("Game is unfinished ATM", 100, 130, 24, 1, 1, sf::Color::White);
		DrawFontGUI("Press R for Next Level", 100, 150, 24, 1, 1, sf::Color::Red);
	}
}
