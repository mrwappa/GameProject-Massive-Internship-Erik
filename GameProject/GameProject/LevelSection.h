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
#include "MageSpawner.h"
#include "LaserEnemy.h"

#include <fstream>
#include <streambuf>
#include <sstream>

#define BRICK '1'
#define WALL '2'
#define ENEMY '3'
#define PLAYER '4'

class LevelSection : public CollisionEntity
{
public:
	LevelSection(float aX, float aY, bool aSectionForPlayer);
	~LevelSection();
	
	static GrowingArray<std::string> Sections;
	static GrowingArray<std::string> PlayerSections;

	static void InitSections();
	static void LoadSection(std::string aPath, GrowingArray<std::string>* aSectionList);
	static float SWidth;
	static float SHeight;

	void Update();
	void Draw();

	float SnapToSectionX(float aIndex);
	float SnapToSectionY(float aIndex);

	void AddSolid(Solid* aSolid);

	GrowingArray<Solid*>* GetSolids();

private:

	int myRows;
	int myColumns;

	bool myCreatePlayerSection;

	GrowingArray<Solid*> mySolids;
};
#endif
