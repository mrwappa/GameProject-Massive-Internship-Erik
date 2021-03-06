#include "stdafx.h"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Window.hpp"
#include "Entity.h"
#include "SFML\OpenGL.hpp"
#include "World.h"
#include "CollisionEntity.h"


int main()
{
	//Check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	//Setup Window
	int width = sf::VideoMode::getDesktopMode().width;
	int height = sf::VideoMode::getDesktopMode().height;
	sf::RenderWindow window(sf::VideoMode(width, height), "WINDOW", sf::Style::None);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(false);
	window.setMouseCursorVisible(true);
	window.setKeyRepeatEnabled(true);
	
	
	Camera camera(0,0,width,height);
	Entity::Camera = &camera;
	GSprite::Camera = &camera;

	GSprite::Window = &window;
	Camera::Window = &window;
	sf::ContextSettings settings;
	//settings.antialiasingLevel = 16;
	/*settings.depthBits = 24;
	settings.stencilBits = 8;*/
	/*settings.majorVersion = 3;
	settings.minorVersion = 0;*/

	sf::Font font;
	if(!font.loadFromFile("Fonts/5x5_square.ttf")){}
	Entity::MainFont = &font;

	Entity::Pixel.SetTexture("Sprites/spr_pixel.png", 1);

	//Input
	InputHandler inputHandler;
	Entity::Input = &inputHandler;
	
	std::thread* sortDrawThread = new std::thread(Entity::SortDrawList);
	Entity::SortDrawThread = sortDrawThread;
	sortDrawThread->detach();
	
	new World();
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
		
		Alarm::DecrementAlarms();
		camera.Update();
		
		window.clear(sf::Color::Color(41, 38, 52,255));
		Entity::DrawAll();
		
		//DRAW GUI
		for (auto const &instance : Entity::SuperList)
		{
			for (int i = 0; i < instance.second->Size(); i++)
			{
				if (instance.second->FindAtIndex(i)->GetDrawing())
				{
					instance.second->FindAtIndex(i)->DrawGUI();
				}
			}
		}
		window.display();

		
		Entity::DeleteMarkedInstances();
		
	}
	
	Entity::SortInDrawThread = false;
	delete sortDrawThread;

	//Deleting all objects in main loop so we don't needlessly exit with a memory leak
	for (auto const &instance : Entity::SuperList)
	{
		for (int i = 0; i < instance.second->Size(); i++)
		{
			instance.second->FindAtIndex(i)->OnRemoval();
		}
	}

	for (auto const &instance : CollisionEntity::CollisionList)
	{
		delete instance.second;
	}

	for (auto const &instance : Entity::SuperList)
	{
		instance.second->DeleteAll();
	}
	for (auto const &instance : Entity::SuperList)
	{
		delete instance.second;
	}
	
	GSprite::DeleteAllSprites();
	CollisionEntity::AStarGrid->DestroyGrid();
	delete CollisionEntity::AStarGrid;
	


	return 0;
}