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
	void BeginUpdate();
	void Draw();

	void CreateWorld();
	void DestroyWorld();
	void DrawGUI();

private:
	bool myCreateWorld;
};

#endif // !WORLD_H