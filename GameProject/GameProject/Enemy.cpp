#include "stdafx.h"
#include "Enemy.h"

Player* Enemy::Target;

Enemy::Enemy()
{
	AddCollInstance("Enemy", this);
}


Enemy::~Enemy()
{
}

void Enemy::OnRemoval()
{
	RemoveCollInstance("Enemy", this);
	CollisionEntity::OnRemoval();
}

void Enemy::StateIdle()
{
}

void Enemy::StateAggro()
{
}

void Enemy::StatePathFind()
{

}
