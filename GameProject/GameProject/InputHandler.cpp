#include "stdafx.h"
#include "InputHandler.h"

sf::Event* InputHandler::Event;
InputHandler::InputHandler()
{
	MouseWheelUp = false;
	MouseWheelDown = false;
}


InputHandler::~InputHandler()
{
}

void InputHandler::Update()
{
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		keyData[i] = keyData[i] > 0 ? -1 : 0;
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
		{
			keyData[i] += 2;
		}
	}

	for (int i = 0; i < sf::Mouse::ButtonCount; i++)
	{
		mouseData[i] = mouseData[i] > 0 ? -1 : 0;
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button)i))
		{
			mouseData[i] += 2;
		}
	}
	/*MouseWheelUp = false;
	MouseWheelDown = false;*/
}

void InputHandler::UpdateMouseWheel()
{
	MouseWheelUp = false;
	MouseWheelDown = false;

	if (Event->type == sf::Event::MouseWheelMoved)
	{
		if (Event->mouseWheel.delta > 0)
		{
			MouseWheelUp = true;
		}
		if (Event->mouseWheel.delta < 0)
		{
			MouseWheelDown = true;
		}
	}
}
