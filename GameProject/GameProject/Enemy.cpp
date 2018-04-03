#include "stdafx.h"
#include "Enemy.h"

Player* Enemy::Target;
sf::Color Enemy::GrabColor = sf::Color::Cyan;

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

void Enemy::StateGrabbable()
{
}

void Enemy::StateGrabbed()
{
}

void Enemy::StateInUse()
{
}

void Enemy::SetState(int aState)
{
	myState = aState;
}

int Enemy::GetState() const
{
	return myState;
}
