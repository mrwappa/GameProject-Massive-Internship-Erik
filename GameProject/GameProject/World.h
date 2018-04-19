#ifndef WORLD_H
#define WORLD_H

#include "Player.h"
#include "Brick.h"
#include "TestEnemy.h"
#include "ProjectileEnemy.h"
#include "Wall.h"
#include "BoxTest.h"
#include "Ground.h"
#include "GroundEdge.h"
#include "GroundPillar.h"
#include "LevelSection.h"

class World : public Entity
{
public:
	World();
	~World();

	void Update();
	void BeginUpdate();
	void Draw();

	void DeactivateAllInstances();
	void DrawLoadingScreen();
	void ReturnFromLoadingScreen();

	void CreateWorld();
	void DestroyWorld();
	void DrawGUI();

private:
	int myWorldHeight;
	int myWorldWidth;

	Alarm myLoadScreenAlarm;
};

#endif // !WORLD_H