#pragma once

#include "SFML\Graphics.hpp"

class GameWindow
{
public:
	enum Event {
		CLOSE
	};

	GameWindow();
	
	bool PollEvent(Event& event);

	sf::RenderWindow* GetRenderWindow();

private:
	sf::RenderWindow mySFMLWindow;
};