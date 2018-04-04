#include "stdafx.h"
#include "World.h"

World::World()
{
	Entity::Init("World", 0, 0);
	mySprite.SetTexture("Sprites/32x32Block.png", 1);
	CreateWorld();
}


World::~World()
{
}

void World::Update()
{
	
}

void World::BeginUpdate()
{
	CreateWorld();
}

void World::Draw()
{
	mySprite.Draw(CollisionEntity::GridSnapMouse().x, CollisionEntity::GridSnapMouse().y, 1, 1, 0, -99999, 1, sf::Color::Black, 0);

	if (MouseCheckPressed(sf::Mouse::Left) and KeyboardCheck(sf::Keyboard::Space))
	{
		new Brick(CollisionEntity::GridSnapMouse().x, CollisionEntity::GridSnapMouse().y);
	}
}

void World::CreateWorld()
{
	if (myCreateWorld)
	{
		AStarNode::NodeSize = 32.0f;
		CollisionEntity::AStarGrid = new AStar(30, 17);
		new Player(7 * 32 + 16, 7 * 32 + 16);
		new Brick(4 * 32 + 16, 4 * 32 + 16);
		new Brick(0, 0);
		new Brick(4 * 32 + 16, 5 * 32 + 16);
		new Brick(4 * 32 + 16, 6 * 32 + 16);
		new TestEnemy(3 * 32 + 16, 4 * 32 + 16);
		new TestEnemy(400, 400);
		new TestEnemy(400 + 40, 400 + 40);
		new TestEnemy(400 - 40, 400 - 40);
		myCreateWorld = false;
	}
	
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
	CollisionEntity::AStarGrid->DestroyGrid();
	delete CollisionEntity::AStarGrid;
	CollisionEntity::AStarGrid = NULL;
}

void World::DrawGUI()
{
	if (KeyboardCheckPressed(sf::Keyboard::R))
	{
		DestroyWorld();
		myCreateWorld = true;
		Camera->SetZoom(1);
	}
}