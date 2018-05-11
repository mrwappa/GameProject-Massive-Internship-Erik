#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Enemy.h"
#include "Player.h"

class Tutorial : public CollisionEntity
{
public:
	Tutorial();
	~Tutorial();

	void Update();
	void DrawGUI();

private:

	enum TutorialState {Walk, Attack, Pickup, UseEnemy, NextLevel};
	int myState;

	bool myWalk[4];
	bool myUseEnemy[2];
};

#endif // !TUTORIAL_H