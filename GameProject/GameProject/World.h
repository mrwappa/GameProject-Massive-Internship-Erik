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

	void CreateWorld(float aRows, float aColumns);
	void DestroyWorld();
	void DrawGUI();

};

#endif // !WORLD_H