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
#include "MapSections.h"
#include "MageSpawner.h"

class World : public Entity
{
public:
	World();
	~World();

	void Update();
	void BeginUpdate();
	void EndUpdate();
	void Draw();

	void DeactivateAllInstances();
	void ActivateAllInstances();
	void DrawPauseScreen();

	void CreateWorld();
	void DestroyWorld();
	void DrawGUI();

	enum GameState {Active, Paused, MainMenu};
	enum WorldState {InAction, Transitioning};
	void StateActive();
	void StatePaused();
	void StateMainMenu();

private:

	int myCurrentLevel;

	std::string myCurrentMap;
	GrowingArray<std::string> myMaps;

	bool mySortDrawList;

	int myWorldState;

	int myGameState;
	int myPrevGameState;
};

#endif // !WORLD_H