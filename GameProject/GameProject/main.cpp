#include "stdafx.h"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Window.hpp"
#include "Entity.h"
#include "SFML\OpenGL.hpp"
#include "Player.h"


int main()
{
	//Check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	glEnable(GL_TEXTURE_2D);

	//Setup Window
	int width = sf::VideoMode::getDesktopMode().width;
	int height = sf::VideoMode::getDesktopMode().height;
	sf::RenderWindow window(sf::VideoMode(width, height), "WINDOW", sf::Style::None);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(true);
	window.setKeyRepeatEnabled(true);

	GSprite::Window = &window;

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 16;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	
	//Input
	InputHandler inputHandler;
	Entity::Input = &inputHandler;
	
	new Player(100, 100, sf::Color::White);
	new Player(110, 110, sf::Color::Red);

	while (window.isOpen())
	{

		sf::Event event;
		InputHandler::Event = &event;
		inputHandler.Update();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			inputHandler.UpdateMouseWheel();
		}

		//BEGIN UPDATE
		for (auto const &instance : Entity::SuperList)
		{
			for (size_t i = 0; i < instance.second->Size(); i++)
			{
				if (instance.second->FindAtIndex(i)->GetActive())
				{
					instance.second->FindAtIndex(i)->BeginUpdate();
				}

			}
		}
		//UPDATE
		for (auto const &instance : Entity::SuperList)
		{
			for (size_t i = 0; i < instance.second->Size(); i++)
			{
				if (instance.second->FindAtIndex(i)->GetActive())
				{
					instance.second->FindAtIndex(i)->Update();
				}
			}
		}

		//END UPDATE
		for (auto const &instance : Entity::SuperList)
		{
			for (size_t i = 0; i < instance.second->Size(); i++)
			{
				if (instance.second->FindAtIndex(i)->GetActive())
				{
					instance.second->FindAtIndex(i)->EndUpdate();
				}
			}
		}

		
		window.clear();
		/*glPushMatrix();
		glTranslatef(x, y, depth);

		glPopMatrix();*/
		glPushMatrix();
		window.resetGLStates();
		//"DRAW"
		for (auto const &instance : Entity::SuperList)
		{
			for (size_t i = 0; i < instance.second->Size(); i++)
			{
				if (instance.second->FindAtIndex(i)->GetActive())
				{
					instance.second->FindAtIndex(i)->Draw();
				}
			}
		}

		window.display();
		glPushMatrix();
		Entity::DeleteMarkedInstances();
	}

	
	return 0;
}
