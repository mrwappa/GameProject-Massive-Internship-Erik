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

	//OpenGL
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	//glClearDepth(1.f);
	
	//Setup Window
	int width = sf::VideoMode::getDesktopMode().width;
	int height = sf::VideoMode::getDesktopMode().height;
	sf::RenderWindow window(sf::VideoMode(width, height), "WINDOW", sf::Style::None);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(true);
	window.setKeyRepeatEnabled(true);

	Camera camera(0,0,width,height);
	Entity::Camera = &camera;

	GSprite::Window = &window;
	Camera::Window = &window;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	/*settings.depthBits = 24;
	settings.stencilBits = 8;*/
	/*settings.majorVersion = 3;
	settings.minorVersion = 0;*/

	
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
		
		camera.Update();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*glPushMatrix();
		glTranslatef(x, y, depth);

		glPopMatrix();*/

		glClear(GL_DEPTH_BUFFER_BIT);
		window.clear();
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
		
		Entity::DeleteMarkedInstances();
	}

	//Deleting all objects in main loop so we don't needlessly exit with a memory leak
	for (auto const &instance : Entity::SuperList)
	{
		for (size_t i = 0; i < instance.second->Size(); i++)
		{
			instance.second->DeleteAll();
		}
	}
	for (auto const &instance : Entity::SuperList)
	{
		delete instance.second;
	}
	//Entity::SuperList.clear();
	
	return 0;
}
