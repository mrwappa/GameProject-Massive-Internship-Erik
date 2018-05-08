#include "stdafx.h"
#include "LevelSection.h"

float LevelSection::SWidth;
float LevelSection::SHeight;

GrowingArray<std::string> LevelSection::Sections;
GrowingArray<std::string> LevelSection::PlayerSections;

LevelSection::LevelSection(float aX, float aY, bool aSectionForPlayer)
{
	Init("LevelSection", aX, aY);

	myRows = SWidth;
	myColumns = SHeight;

	myBoxWidth = AStarNode::NodeSize * myRows;
	myBoxHeight = AStarNode::NodeSize * myColumns;

	myDepth = 1000;

	myCreatePlayerSection = aSectionForPlayer;

	//CREATE OBJECTS IN MAP/SECTION
	int rand;
	std::string level;
	if (myCreatePlayerSection)
	{
		rand = Math::IRand(0, PlayerSections.Size() - 1);
		level = std::string(PlayerSections[rand]);
	}
	else
	{
		rand = Math::IRand(0, Sections.Size() - 1);
		level = std::string(Sections[rand]);
	}

	int row = 0;
	int column = 0;

	for (int i = 0; i < level.size(); i++)
	{
		if (level[i] == '\n')
		{
			row++;
			column = 0;
		}
		else if (level[i] != ',' and level[i] != '\n')
		{
			
			if (level[i] == BRICK)
			{
				AddSolid(new Brick(SnapToSectionX(column), SnapToSectionY(row)));
			}
			else if (level[i] == WALL)
			{
				AddSolid(new Wall(SnapToSectionX(column), SnapToSectionY(row)));
			}
			else if (level[i] == ENEMY)
			{
				int rand = Math::IRand(0, 100);

				if (rand > 90)
				{
					new MageSpawner(SnapToSectionX(column), SnapToSectionY(row));
				}
				else if (rand <= 90 and rand > 70)
				{
					new LaserEnemy(SnapToSectionX(column), SnapToSectionY(row));
				}
				else if (rand <= 70 and rand > 30)
				{
					new TestEnemy(SnapToSectionX(column), SnapToSectionY(row));
				}
				else
				{
					new ProjectileEnemy(SnapToSectionX(column), SnapToSectionY(row));
				}
			}
			else if (level[i] == PLAYER)
			{
				if (Enemy::Target == NULL)
				{
					new Player(SnapToSectionX(column), SnapToSectionY(row));
				}
				else if (Enemy::Target != NULL)
				{
					Enemy::Target->SetX(SnapToSectionX(column));
					Enemy::Target->SetY(SnapToSectionY(row));
				}
			}
			column++;
		}
	}
}

LevelSection::~LevelSection()
{
}

void LevelSection::InitSections()
{
	//Regular
	LoadSection("Maps/sect1.txt",&Sections);
	LoadSection("Maps/sect2.txt",&Sections);
	LoadSection("Maps/sect3.txt",&Sections);
	LoadSection("Maps/sect4.txt",&Sections);
	LoadSection("Maps/sect5.txt",&Sections);
	LoadSection("Maps/sect6.txt",&Sections);

	//Player Spawn
	LoadSection("Maps/player_sect1.txt", &PlayerSections);
	LoadSection("Maps/player_sect2.txt", &PlayerSections);
	LoadSection("Maps/player_sect3.txt", &PlayerSections);

}

void LevelSection::LoadSection(std::string aPath, GrowingArray<std::string>* aSectionList)
{
	std::ifstream fileStream; 
	fileStream.open(aPath);
	std::stringstream strStream;
	strStream << fileStream.rdbuf();
	 
	fileStream.close();
	aSectionList->Add(std::string(strStream.str()));
}

void LevelSection::Update()
{
	bool sectionU = ObjPosition(myX, myY - myBoxHeight, "LevelSection");
	bool sectionD = ObjPosition(myX, myY + myBoxHeight, "LevelSection");
	bool sectionL = ObjPosition(myX - myBoxWidth, myY, "LevelSection");
	bool sectionR = ObjPosition(myX + myBoxWidth, myY, "LevelSection");

	for (int i = 0; i < myRows; i++)
	{
		for (int j = 0; j < myColumns; j++)
		{
			if (i == 0 and j == 0)//UP LEFT
			{
				if (sectionU and !sectionL)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Left));
				}
				else if (sectionL and !sectionU)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Up));
				}
				else if (sectionL and sectionU)
				{
					new Ground(SnapToSectionX(i), SnapToSectionY(j));
				}
				else
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::UpLeft));
				}
					
			}
			else if (i == myRows - 1 and j == 0)//UP RIGHT
			{
				if (sectionU and !sectionR)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Right));
				}
				else if (sectionR and !sectionU)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Up));
				}
				else if (sectionR and sectionU)
				{
					new Ground(SnapToSectionX(i), SnapToSectionY(j));
				}
				else
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::UpRight));
				}
			}
			else if (i == 0 and j == myColumns - 1)//DOWN LEFT
			{
				if (sectionD and !sectionL)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Left));
				}
				else if (sectionL and !sectionD)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Down));
					new GroundPillar(SnapToSectionX(i), SnapToSectionY(j) + 64, GroundPillar::Middle);
				}
				else if (sectionL and sectionD)
				{
					new Ground(SnapToSectionX(i), SnapToSectionY(j));
				}
				else
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::DownLeft));
					new GroundPillar(SnapToSectionX(i), SnapToSectionY(j) + 64, GroundPillar::Left);
				}
			}
			else if (i == myRows - 1 and j == myColumns - 1)//DOWN RIGHT
			{
				if (sectionD and !sectionR)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Right));
				}
				else if (sectionR and !sectionD)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Down));
					new GroundPillar(SnapToSectionX(i), SnapToSectionY(j) + 64, GroundPillar::Middle);
				}
				else if (sectionR and sectionD)
				{
					new Ground(SnapToSectionX(i), SnapToSectionY(j));
				}
				else
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::DownRight));
					new GroundPillar(SnapToSectionX(i), SnapToSectionY(j) + 64, GroundPillar::Right);
				}
			}
			else if (i == 0 and j > 0 and j <= myColumns)//LEFT
			{
				if (!sectionL)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Left));
				}
				else
				{
					new Ground(SnapToSectionX(i), SnapToSectionY(j));
				}
			}
			else if (i > 0 and i <= myRows and j == 0)//UP
			{
				if (!sectionU)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Up));
				}
				else
				{
					new Ground(SnapToSectionX(i), SnapToSectionY(j));
				}
			}
			else if (i > 0 and i <= myRows and j == myColumns - 1)//DOWN
			{
				if (!sectionD)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Down));
					new GroundPillar(SnapToSectionX(i), SnapToSectionY(j) + 64, GroundPillar::Middle);
				}
				else
				{
					new Ground(SnapToSectionX(i), SnapToSectionY(j));
				}
			}
			else if (i == myRows - 1 and j > 0 and j <= myColumns)//RIGHT
			{
				if (!sectionR)
				{
					AddSolid(new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Right));
				}
				else
				{
					new Ground(SnapToSectionX(i), SnapToSectionY(j));
				}
			}
			else
			{
				new Ground(SnapToSectionX(i), SnapToSectionY(j));
			}
		}
	}
	myActive = false;
	myOutOfLoop = true;
}

void LevelSection::Draw()
{
	//DrawBBox();
}

float LevelSection::SnapToSectionX(float aIndex)
{
	return aIndex * AStarNode::NodeSize + (AStarNode::NodeSize / 2) + myX - myBoxWidth / 2;
}

float LevelSection::SnapToSectionY(float aIndex)
{
	return aIndex * AStarNode::NodeSize + (AStarNode::NodeSize / 2) + myY - myBoxHeight / 2;
}

void LevelSection::AddSolid(Solid* aSolid)
{
	mySolids.Add(aSolid);
}

GrowingArray<Solid*>* LevelSection::GetSolids()
{
	return &mySolids;
}
