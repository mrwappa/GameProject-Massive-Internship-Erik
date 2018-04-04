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

void Enemy::StateThrown()
{
	if (myState == Thrown)
	{
		myX += myXSpeed;
		myY += myYSpeed;
		
		myXSpeed = Math::Lerp(myXSpeed, 0, 0.2f);
		myYSpeed = Math::Lerp(myYSpeed, 0, 0.2f);
	}
}

void Enemy::Throw(float aSpeed, float aDir)
{
	myDirection = aDir;
	myXSpeed = Math::LenDirX(aSpeed, aDir);
	myYSpeed = Math::LenDirY(aSpeed, aDir);
	myState = Thrown;
}

void Enemy::SetState(int aState)
{
	myState = aState;
}

int Enemy::GetState() const
{
	return myState;
}
