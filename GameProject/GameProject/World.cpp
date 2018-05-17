#include "stdafx.h"
#include "World.h"

int World::EnemyCount;
unsigned long int World::Score;

World::World()
{
	Score = 0;
	EnemyCount = 0;
	myPrevGameState = -1;//not necessary?
	myGameState = Active;

	myWorldState = InAction;
	Camera->SetZoom(0.0005f);

	Entity::Init("World", 0, 0);
	LevelSection::InitSections();
	mySprite.SetTexture("Sprites/32x32Block.png", 1);
	myCurrentLevel = 0;
	CreateWorld();

	myDepth = 99999;
	mySortDrawList = false;

	myTutorial = new Tutorial();
}

World::~World()
{
}

void World::BeginUpdate()
{
}

void World::Update()
{
	
}

void World::EndUpdate()
{

	StatePaused();
	StateMainMenu();
	StateActive();
	if (mySortDrawList)
	{
		SortInDrawThread = false;
		if (DrawList.Size() > 1)
		{
			QuickSort(0, DrawList.Size() - 1);
		}
		//BubbleSort();
		SortInDrawThread = true;
		mySortDrawList = false;

		myWorldState = InAction;
	}
}

void World::Draw()
{

}

void World::CreateWorld()
{
	if (myTutorial != NULL)
	{
		DeleteInstance(myTutorial);
		myTutorial = NULL;
	}

	AStarNode::NodeSize = 32.0f;
	LevelSection::SWidth = 17;
	LevelSection::SHeight = 13;

	myCurrentLevel++;

	if (myCurrentLevel == 1)
	{
		myCurrentMap = SECT_START;
		CollisionEntity::AStarGrid = new AStar(LevelSection::SWidth * 2, LevelSection::SHeight * 1);
	}
	else if (myCurrentLevel == 2)
	{
		myMaps.Add(SECT1_A);
		myMaps.Add(SECT1_B);
		myMaps.Add(SECT1_C);
		myMaps.Add(SECT1_D);
		myMaps.Add(SECT1_E);
		CollisionEntity::AStarGrid = new AStar(LevelSection::SWidth * 2, LevelSection::SHeight * 2);
	}
	else if (myCurrentLevel == 3)
	{
		myMaps.Add(SECT2_A);
		myMaps.Add(SECT2_B);
		myMaps.Add(SECT2_C);
		myMaps.Add(SECT2_D);
		myMaps.Add(SECT2_E);
		CollisionEntity::AStarGrid = new AStar(LevelSection::SWidth * 3, LevelSection::SHeight * 2);
	}
	else if (myCurrentLevel >= 4)
	{
		myMaps.Add(SECT3_A);
		myMaps.Add(SECT3_B);
		myMaps.Add(SECT3_C);
		myMaps.Add(SECT3_D);
		myMaps.Add(SECT3_E);
		CollisionEntity::AStarGrid = new AStar(LevelSection::SWidth * 4, LevelSection::SHeight * 3);
	}
	
	if (myCurrentLevel != 1)
	{
		int rand = Math::IRand(0, myMaps.Size()-1);
		myCurrentMap = myMaps[rand];
		myMaps.RemoveAll();
	}

	int nrOfCells = 0;
	switch (myCurrentMap.size())
	{
	case SECTST_SIZE:
		nrOfCells = SECTST_CELLS;
		break;

	case SECT1_SIZE:
		nrOfCells = SECT1_CELLS;
		break;

	case SECT2_SIZE:
		nrOfCells = SECT2_CELLS;
		break;

	case SECT3_SIZE:
		nrOfCells = SECT3_CELLS;
		break;

	default:
		break;
	}


	int currentCell = 0;
	int playerSection = 1;
	int row = 0;
	int column = 0;
	int rand = 0;

	for (int i = 0; i < myCurrentMap.size(); i++)
	{
		if (myCurrentMap[i] == 'n')
		{
			row++;
			column = 0;
		}
		else if (myCurrentMap[i] == '0' or myCurrentMap[i] == '1')
		{
			if (currentCell == nrOfCells - 1 and playerSection == 1 and myCurrentMap[i] == '1')
			{
				new LevelSection((LevelSection::SWidth * AStarNode::NodeSize / 2) + LevelSection::SWidth * AStarNode::NodeSize * column,
					(LevelSection::SHeight * AStarNode::NodeSize / 2) + LevelSection::SHeight * AStarNode::NodeSize * row, true);
				currentCell++;
			}
			else if (myCurrentMap[i] == '1')
			{
				rand = Math::IRand(0, 2);
				if (rand == 2 and playerSection == 1)
				{
					playerSection = 0;
					new LevelSection((LevelSection::SWidth * AStarNode::NodeSize / 2) + LevelSection::SWidth * AStarNode::NodeSize * column,
						(LevelSection::SHeight * AStarNode::NodeSize / 2) + LevelSection::SHeight * AStarNode::NodeSize * row, true);
				}
				else
				{
					new LevelSection((LevelSection::SWidth * AStarNode::NodeSize / 2) + LevelSection::SWidth * AStarNode::NodeSize * column,
						(LevelSection::SHeight * AStarNode::NodeSize / 2) + LevelSection::SHeight * AStarNode::NodeSize * row,false);
				}
				currentCell++;
			}
			column++;
		}
	}
	
	mySortDrawList = true;
}

void World::DestroyWorld()
{
	for (auto const &instance : Entity::SuperList)
	{
		for (int i = 0; i < instance.second->Size(); i++)
		{
			if (Enemy::Target != NULL)
			{
				if (instance.second->FindAtIndex(i) != this and
					instance.second->FindAtIndex(i) != Enemy::Target and
					instance.second->FindAtIndex(i) != Enemy::Target->GrabbableEnemy)
				{
					DeleteInstance(instance.second->FindAtIndex(i));
				}
			}
			else
			{
				if (instance.second->FindAtIndex(i) != this)
				{
					DeleteInstance(instance.second->FindAtIndex(i));
				}
			}
			
		}
	}

	CollisionEntity::AStarGrid->DestroyGrid();
	delete CollisionEntity::AStarGrid;
	CollisionEntity::AStarGrid = NULL;
}

void World::DrawGUI()
{
	if (myGameState == Paused)
	{
		DrawPauseScreen();
	}
	else if(myGameState == Active and myWorldState == InAction)
	{
		if (EnemyCount == 0)
		{
			if (Enemy::Target != NULL and Enemy::Target->GetState() != Player::Dead)
			{
				DrawFontGUI("Press R for next level", (Camera->GetInitialWidth() / 2) * 0.6f, (Camera->GetInitialHeight() / 2)* 1.4f, 24, 1, 1, sf::Color::White);
			}

			if (KeyboardCheckPressed(sf::Keyboard::R))
			{
				myWorldState = Transitioning;
			}
		}
		else
		{
			if (Score == 0)
			{
				Score = 1;
			}

			if(Enemy::Target != NULL and Enemy::Target->GetState() != Player::Dead)
			Score--;
		}
		DrawFontGUI(std::to_string(Score), 50, 50, 24, 1, 1, sf::Color::White);
	}
}

void World::RestartWorld()
{
	Score = 0;
	EnemyCount = 0;
	myCurrentLevel = 0;
	myWorldState = Transitioning;
}

void World::StateActive()
{
	if (myGameState == Active)
	{
		if (myPrevGameState == Paused)
		{
			ActivateAllInstances();
		}
		if (KeyboardCheckPressed(sf::Keyboard::Return) and myPrevGameState != Paused)
		{
			myGameState = Paused;
		}
		myPrevGameState = Active;
	}
}

void World::StatePaused()
{
	if (myGameState == Paused)
	{
		DeactivateAllInstances();
		
		if (KeyboardCheckPressed(sf::Keyboard::Return))
		{
			myPrevGameState = Paused;
			myGameState = Active;
		}
	}
	else
	{
		if (myWorldState == Transitioning)
		{
			Camera->SetZoom(Math::Lerp(Camera->GetZoom(), 0.0005f, 0.3f));
			if (Camera->GetZoom() < 0.00051f and !mySortDrawList)
			{
				DestroyWorld();
				CreateWorld();
			}
		}
		else if (myWorldState == InAction)
		{
			Camera->SetZoom(Math::Lerp(Camera->GetZoom(), 1.0f, 0.15f));
		}
	}
}

void World::StateMainMenu()
{

}

void World::DeactivateAllInstances()
{
	for (auto const &instance : Entity::SuperList)
	{
		for (int i = 0; i < instance.second->Size(); i++)
		{
			Entity* anInstance = instance.second->FindAtIndex(i);
			if (anInstance != this)
			{
				anInstance->SetActive(false);
				anInstance->SetDrawing(false);
			}
		}
	}
}

void World::ActivateAllInstances()
{
	for (auto const &instance : Entity::SuperList)
	{
		for (int i = 0; i < instance.second->Size(); i++)
		{
			Entity* anInstance = instance.second->FindAtIndex(i);
			if (anInstance != this)
			{
				if (!anInstance->GetOutOfLoop())
				{
					anInstance->SetActive(true);
				}
				anInstance->SetDrawing(true);
			}
		}
	}
}

void World::DrawPauseScreen()
{
	DrawRectGUI(Camera->GetViewWidth() / 2, Camera->GetViewHeight() / 2, Camera->GetViewWidth(), Camera->GetViewHeight(), 0, 1, sf::Color::Black);
	DrawFontGUI("Paused", (Camera->GetInitialWidth() / 2) * 0.8f, (Camera->GetInitialHeight() / 2)* 0.9f, 32, 1, 1, sf::Color::White);
}