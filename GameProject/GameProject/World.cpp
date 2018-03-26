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
	if (KeyboardCheckPressed(sf::Keyboard::R))
	{
		DestroyWorld();
		CreateWorld();
		Camera->SetZoom(1);
	}
}

void World::CreateWorld()
{
	new Player(100, 100);
	new Brick(50, 50);
	new Brick(0, 0);
	new Brick(25, 25);
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
