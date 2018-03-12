#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "SFML\Window.hpp"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	static sf::Event* Event;

	void Update();
	void UpdateMouseWheel();

	bool MouseWheelUp;
	bool MouseWheelDown;

	int keyData[sf::Keyboard::KeyCount];
	int mouseData[sf::Mouse::ButtonCount];

};
#endif // !INPUTHANDLER_H