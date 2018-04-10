#include "stdafx.h"
#include "World.h"

World::World()
{
	Entity::Init("World", 0, 0);
	mySprite.SetTexture("Sprites/32x32Block.png", 1);
	CreateWorld(30,17);

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
	mySprite.Draw(CollisionEntity::GridSnapMouse().x, CollisionEntity::GridSnapMouse().y, 1, 1, 0, 1, sf::Color::Black, 0);

	if (MouseCheckPressed(sf::Mouse::Left) and KeyboardCheck(sf::Keyboard::Space))
	{
		new Brick(CollisionEntity::GridSnapMouse().x, CollisionEntity::GridSnapMouse().y);
	}
	if (MouseCheckPressed(sf::Mouse::Left) and KeyboardCheck(sf::Keyboard::LShift))
	{
		new Wall(CollisionEntity::GridSnapMouse().x, CollisionEntity::GridSnapMouse().y);
	}
}

void World::CreateWorld(float aRows, float aColumns)
{
	AStarNode::NodeSize = 32.0f;
	CollisionEntity::AStarGrid = new AStar(aRows, aColumns);


	for (int i = 0; i < aRows; i++)
	{
		for (int j = 0; j < aColumns; j++)
		{
			if (i == 0 and j == 0)
			{
				new GroundEdge(i * AStarNode::NodeSize, j * AStarNode::NodeSize, GroundEdge::UpLeft);
			}
			else if (i == aRows - 1 and j == 0)
			{
				new GroundEdge(i * AStarNode::NodeSize, j * AStarNode::NodeSize, GroundEdge::UpRight);
			}
			else if (i == 0 and j == aColumns - 1)
			{
				new GroundEdge(i * AStarNode::NodeSize, j * AStarNode::NodeSize, GroundEdge::DownLeft);
				new GroundPillar(i * AStarNode::NodeSize, j * AStarNode::NodeSize + 64, GroundPillar::Left);
			}
			else if (i == aRows - 1 and j == aColumns - 1)
			{
				new GroundEdge(i * AStarNode::NodeSize, j * AStarNode::NodeSize, GroundEdge::DownRight);
				new GroundPillar(i * AStarNode::NodeSize, j * AStarNode::NodeSize + 64, GroundPillar::Right);
			}
			else if (i == 0 and j > 0 and j <= aColumns)
			{
				new GroundEdge(i * AStarNode::NodeSize, j * AStarNode::NodeSize, GroundEdge::Left);
			}
			else if (i > 0 and i <= aRows and j == 0)
			{
				new GroundEdge(i * AStarNode::NodeSize, j * AStarNode::NodeSize, GroundEdge::Up);
			}
			else if (i > 0 and i <= aRows and j == aColumns -1)
			{
				new GroundEdge(i * AStarNode::NodeSize, j * AStarNode::NodeSize, GroundEdge::Down);
				new GroundPillar(i * AStarNode::NodeSize, j * AStarNode::NodeSize + 64, GroundPillar::Middle);
			}
			else if (i == aRows -1 and j > 0 and j <= aColumns)
			{
				new GroundEdge(i * AStarNode::NodeSize, j * AStarNode::NodeSize, GroundEdge::Right);
			}
			else
			{
				new Ground(i * AStarNode::NodeSize, j * AStarNode::NodeSize);
			}
		}
	}

	new Player(7 * 32 + 16, 7 * 32 + 16);
	new Brick(4 * 32 + 16, 4 * 32 + 16);
	new Brick(4 * 32 + 16, 5 * 32 + 16);
	new Brick(4 * 32 + 16, 6 * 32 + 16);
	new Wall(4 * 32 + 16, 7 * 32 + 16);
	new TestEnemy(3 * 32 + 16, 4 * 32 + 16);
	new ProjectileEnemy(400, 400);
	new TestEnemy(400 + 40, 400 + 40);
	new TestEnemy(400 - 40, 400 - 40);
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
		CreateWorld(30, 17);
		Camera->SetZoom(1);
	}
}