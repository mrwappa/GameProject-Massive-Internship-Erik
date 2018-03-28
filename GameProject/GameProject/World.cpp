#include "stdafx.h"
#include "World.h"



World::World()
{
	Entity::Init("World", 0, 0);
	CreateWorld();
}


World::~World()
{
}

void World::Update()
{
	
}

void World::CreateWorld()
{
	new Player(100, 100);
	new Brick(68.5f, 40.5f);
	new Brick(34.5f, 25.5f);
	new Brick(0.5f, 25.5f);
	new TestEnemy(-40, -40);
}

void World::DestroyWorld()
{
	for (auto const &instance : Entity::SuperList)
	{
		for (int i = 0; i < instance.second->Size(); i++)
		{
			if (instance.second->FindAtIndex(i) != this)
			{
				DeleteInstance(instance.second->FindAtIndex(i));
			}
		}
	}
}

void World::DrawGUI()
{
	//This is done in DrawGUI() because otherwise two of every objects Sprite will be drawn on one frame
	//It's nitpicky but also something annoying that I'd rather not deal with.
	if (KeyboardCheckPressed(sf::Keyboard::R))
	{
		DestroyWorld();
		CreateWorld();
		Camera->SetZoom(1);
	}
}
