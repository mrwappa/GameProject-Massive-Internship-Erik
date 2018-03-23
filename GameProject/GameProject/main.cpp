#include "stdafx.h"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Window.hpp"
#include "Entity.h"
#include "SFML\OpenGL.hpp"
#include "Player.h"
#include "Brick.h"

int main()
{
	//Check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
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
	GSprite::Camera = &camera;

	GSprite::Window = &window;
	Camera::Window = &window;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	/*settings.depthBits = 24;
	settings.stencilBits = 8;*/
	/*settings.majorVersion = 3;
	settings.minorVersion = 0;*/

	sf::Texture pixel;
	if (!pixel.loadFromFile("Sprites/spr_pixel.png")) {}
	Entity::Pixel.setTexture(pixel);

	//Input
	InputHandler inputHandler;
	Entity::Input = &inputHandler;
	
	/*for (size_t i = 0; i < 500; i++)
	{
		new Player(100 + i * 2, 100 + i * 2);
	}*/
	new Player(100, 100);
	new Brick(50, 50);

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
			for (int i = 0; i < instance.second->Size(); i++)
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
			for (int i = 0; i < instance.second->Size(); i++)
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
			for (int i = 0; i < instance.second->Size(); i++)
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

		//"DRAW"
		for (auto const &instance : Entity::SuperList)
		{
			for (int i = 0; i < instance.second->Size(); i++)
			{
				if (instance.second->FindAtIndex(i)->GetActive())
				{
					instance.second->FindAtIndex(i)->Draw();
				}
			}
		}
		
		window.clear(sf::Color::Color(100,149,237,255));
		GSprite::DrawAllSprites();
		//DRAW GUI
		for (auto const &instance : Entity::SuperList)
		{
			for (int i = 0; i < instance.second->Size(); i++)
			{
				if (instance.second->FindAtIndex(i)->GetActive())
				{
					instance.second->FindAtIndex(i)->DrawGUI();
				}
			}
		}
		window.display();
		
		Entity::DeleteMarkedInstances();
	}

	//Deleting all objects in main loop so we don't needlessly exit with a memory leak
	for (auto const &instance : Entity::SuperList)
	{
		for (int i = 0; i < instance.second->Size(); i++)
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
