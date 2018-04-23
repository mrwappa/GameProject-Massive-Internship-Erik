#include "stdafx.h"
#include "World.h"


World::World()
{
	myPrevState = -1;
	myState = Active;

	Entity::Init("World", 0, 0);
	LevelSection::InitSections();
	mySprite.SetTexture("Sprites/32x32Block.png", 1);
	myCurrentLevel = 0;
	CreateWorld();

	myDepth = 99999;
	mySortDrawList = false;
}


World::~World()
{
	LevelSection::Sections.DeleteAll();
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
	myPrevState = myState;
}

void World::EndUpdate()
{
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
	}


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
	AStarNode::NodeSize = 32.0f;
	LevelSection::SWidth = 16;
	LevelSection::SHeight = 12;

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

	int row = 0;
	int column = 0;

	for (int i = 0; i < myCurrentMap.size(); i++)
	{
		if (myCurrentMap[i] == 'n')
		{
			row++;
			column = 0;
		}
		else if (myCurrentMap[i] == '0' or myCurrentMap[i] == '1')
		{
			if (myCurrentMap[i] == '1')
			{
				new LevelSection((LevelSection::SWidth * AStarNode::NodeSize / 2) + LevelSection::SWidth * AStarNode::NodeSize * column,
					(LevelSection::SHeight * AStarNode::NodeSize / 2) + LevelSection::SHeight * AStarNode::NodeSize * row, "Maps/Test2.txt");
			}
			column++;
		}
	}

	new Player(7 * 32 + 16, 7 * 32 + 16);
	/*new TestEnemy(3 * 32 + 16, 4 * 32 + 16);
	new ProjectileEnemy(300, 300);
	new TestEnemy(300 + 20, 350 + 20);
	new TestEnemy(300 - 40 + 20, 350 - 40 + 20);
	new TestEnemy(3 * 32 + 16, 4 * 32 + 16);	
	new TestEnemy(300 + 20, 350 + 20);
	new ProjectileEnemy(300, 300);
	new TestEnemy(300 - 40 + 20, 350 - 40 + 20);
	new MageSpawner(7 * 32 + 32, 7 * 32 + 32);*/

	//SetDrawList();
	/*new BoxTest(300, 300, true);
	new BoxTest(300 + 42, 300, false);*/
	
	mySortDrawList = true;
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
		//DeactivateAllInstances();
		//DrawListUnfinished = true;
		Camera->SetZoom(1);
	}

	StatePaused();
	StateMainMenu();
	StateActive();

}

void World::PauseGame()
{
	myState = Paused;
}

void World::ResumeGame()
{
	myState = Active;
}

void World::StateActive()
{
	if (myState == Active)
	{
		if (myPrevState != Paused)
		{
			if (KeyboardCheckPressed(sf::Keyboard::Return))
			{
				myState = Paused;
			}
		}
		else
		{
			ActivateAllInstances();
		}
	}
}

void World::StatePaused()
{
	if (myState == Paused)
	{
		DeactivateAllInstances();
		DrawPauseScreen();
		myPrevState = Paused;
		if (KeyboardCheckPressed(sf::Keyboard::Return))
		{
			myState = Active;
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
	DrawFontGUI("Paused", (Camera->GetViewWidth() / 2) * 0.8f, (Camera->GetViewHeight() / 2)* 0.9f, 32, 1, 1, sf::Color::White);
}

void World::ReturnFromLoadingScreen()
{
	Entity* player = GetObj("Player");
	if (player != NULL and !player->GetActive())
	{
		for (auto const &instance : Entity::SuperList)
		{
			for (int i = 0; i < instance.second->Size(); i++)
			{
				instance.second->FindAtIndex(i)->SetActive(true);
			}
		}
	}
}