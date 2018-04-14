#include "stdafx.h"
#include "LevelSection.h"


LevelSection::LevelSection(float aX, float aY, std::string aSection)
{
	Init("LevelSection", aX, aY);

	myRows = 16;
	myColumns = 12;

	myBoxWidth = AStarNode::NodeSize * myRows;
	myBoxHeight = AStarNode::NodeSize * myColumns;

	//make the object not update anymore instead of checking a bool
	myCheckAdjacent = true;
	mySection = aSection;

	myDepth = 1000;
}


LevelSection::~LevelSection()
{
}

void LevelSection::Update()
{
	if (myCheckAdjacent)
	{
		for (int i = 0; i < myRows; i++)
		{
			for (int j = 0; j < myColumns; j++)
			{
				if (i == 0 and j == 0)
				{
					new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::UpLeft);
				}
				else if (i == myRows - 1 and j == 0)
				{
					new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::UpRight);
				}
				else if (i == 0 and j == myColumns - 1)
				{
					new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::DownLeft);
					new GroundPillar(SnapToSectionX(i), SnapToSectionY(j) + 64, GroundPillar::Left);
				}
				else if (i == myRows - 1 and j == myColumns - 1)
				{
					new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::DownRight);
					new GroundPillar(SnapToSectionX(i), SnapToSectionY(j) + 64, GroundPillar::Right);
				}
				else if (i == 0 and j > 0 and j <= myColumns)
				{
					new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Left);
				}
				else if (i > 0 and i <= myRows and j == 0)
				{
					new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Up);
				}
				else if (i > 0 and i <= myRows and j == myColumns - 1)
				{
					new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Down);
					new GroundPillar(SnapToSectionX(i), SnapToSectionY(j) + 64, GroundPillar::Middle);
				}
				else if (i == myRows - 1 and j > 0 and j <= myColumns)
				{
					new GroundEdge(SnapToSectionX(i), SnapToSectionY(j), GroundEdge::Right);
				}
				else
				{
					new Ground(SnapToSectionX(i), SnapToSectionY(j));
				}
			}
		}

		std::ifstream textFile(mySection);
		std::string level;

		textFile.seekg(0, std::ios::end);
		level.reserve(textFile.tellg());
		textFile.seekg(0, std::ios::beg);

		level.assign(std::istreambuf_iterator<char>(textFile), std::istreambuf_iterator<char>());

		int row = 0;
		int column = 0;

		for (int i = 0; i < level.size(); i++)
		{
			if (level[i] == '\n')
			{
				row++;
				column = 0;
			}
			else if(level[i] != ',' and level[i] != '\n')
			{
				column++;
				if (level[i] == BRICK)
				{
					new Brick(SnapToSectionX(column), SnapToSectionY(row));
				}
				else if (level[i] == WALL)
				{
					new Wall(SnapToSectionX(column), SnapToSectionY(row));
				}
			}
		}

		myCheckAdjacent = false;
	}
}

void LevelSection::Draw()
{
	DrawBBox();
}

float LevelSection::SnapToSectionX(float aIndex)
{
	return aIndex * AStarNode::NodeSize + (AStarNode::NodeSize / 2) + myX - myBoxWidth / 2;
}

float LevelSection::SnapToSectionY(float aIndex)
{
	return aIndex * AStarNode::NodeSize + (AStarNode::NodeSize / 2) + myY - myBoxHeight / 2;
}
