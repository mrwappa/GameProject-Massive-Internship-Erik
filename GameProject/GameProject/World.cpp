#include "stdafx.h"
#include "World.h"

World::World()
{
	Entity::Init("World", 0, 0);
	mySprite.SetTexture("Sprites/32x32Block.png", 1);
	
	myWorldWidth = 0;
	myWorldHeight = 0;
	CreateWorld();

	myDepth = 99999;
}


World::~World()
{
}

void World::Update()
{
	/*CollisionEntity::SlowMo = Math::Lerp(CollisionEntity::SlowMo, 1, 0.3f);
	if(KeyboardCheck(sf::Keyboard::X))
	{
		CollisionEntity::SlowMo = 4;
	}*/
}

void World::BeginUpdate()
{
}

void World::Draw()
{
	/*mySprite.Draw(CollisionEntity::GridSnapMouse().x, CollisionEntity::GridSnapMouse().y, 1, 1, 0, 1, sf::Color::Black, 0);

	if (MouseCheckPressed(sf::Mouse::Left) and KeyboardCheck(sf::Keyboard::Space))
	{
		new Brick(CollisionEntity::GridSnapMouse().x, CollisionEntity::GridSnapMouse().y);
	}
	if (MouseCheckPressed(sf::Mouse::Left) and KeyboardCheck(sf::Keyboard::LShift))
	{
		new Wall(CollisionEntity::GridSnapMouse().x, CollisionEntity::GridSnapMouse().y);
	}*/
}

void World::CreateWorld()
{
	myWorldWidth++;
	myWorldHeight++;
	AStarNode::NodeSize = 32.0f;
	LevelSection::SWidth = 16;
	LevelSection::SHeight = 12;
	
	CollisionEntity::AStarGrid = new AStar(LevelSection::SWidth * myWorldWidth, LevelSection::SHeight * myWorldHeight);
	
	for (int i = 0; i < myWorldHeight; i++)
	{
		for (int j = 0; j < myWorldWidth; j++)
		{
			new LevelSection((LevelSection::SWidth * AStarNode::NodeSize / 2) + LevelSection::SWidth * AStarNode::NodeSize * j,
							 (LevelSection::SHeight * AStarNode::NodeSize / 2) + LevelSection::SHeight * AStarNode::NodeSize * i, "Maps/Test1.txt");
		}
	}

	new Player(7 * 32 + 16, 7 * 32 + 16);
	new TestEnemy(3 * 32 + 16, 4 * 32 + 16);
	new ProjectileEnemy(300, 300);
	new TestEnemy(300 , 350);
	new TestEnemy(300 - 40, 350 - 40);
	/*new BoxTest(300, 300, true);
	new BoxTest(300 + 42, 300, false);*/
	
	
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
		CreateWorld();
		Camera->SetZoom(1);
	}
}