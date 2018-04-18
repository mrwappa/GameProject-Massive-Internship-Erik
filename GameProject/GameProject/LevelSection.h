#ifndef LEVELSECTION_H
#define LEVELSECTION_H

#include "Player.h"
#include "Brick.h"
#include "TestEnemy.h"
#include "ProjectileEnemy.h"
#include "Wall.h"
#include "BoxTest.h"
#include "Ground.h"
#include "GroundEdge.h"
#include "GroundPillar.h"
#include <fstream>
#include <streambuf>

#define BRICK '1'
#define WALL '2'

class LevelSection : public CollisionEntity
{
public:
	LevelSection(float aX, float aY, std::string aSection);
	~LevelSection();

	static float SWidth;
	static float SHeight;

	void Update();
	void Draw();

	float SnapToSectionX(float aIndex);
	float SnapToSectionY(float aIndex);

private:

	std::string mySection;
	bool myCheckAdjacent;

	int myRows;
	int myColumns;
};
#endif
