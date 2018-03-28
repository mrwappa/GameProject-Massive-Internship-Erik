#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include "Player.h"
#include "Brick.h"
#include "TestEnemy.h"

class World : public Entity
{
public:
	World();
	~World();

	void Update();

	void CreateWorld();
	void DestroyWorld();
	void DrawGUI();
	
};

#endif // !WORLD_H