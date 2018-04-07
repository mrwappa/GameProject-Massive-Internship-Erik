#include "stdafx.h"
#include "ProjectileEnemy.h"


ProjectileEnemy::ProjectileEnemy(float aX, float aY)
{
	Init("ProjectileEnemy", aX, aY);
	myState = Aggro;
	mySprite.SetTexture("Sprites/Enemies/spr_floating_enemy.png", 1);

	myBoxWidth = 12;
	myBoxHeight = 12;

	myXScale = 2;
	myYScale = myXScale;
	myZ = 20;

	myMoveSpeed = 1.5f;

	myAttackTimer = Math::FRand(2, 5);
	myHP = 10;
}


ProjectileEnemy::~ProjectileEnemy()
{
}

void ProjectileEnemy::StateAggro()
{
	if (myState == Aggro)
	{
		myAttackTimer -= 1.0f / 60.0f;
		if (myAttackTimer <= 0)
		{
			myAttackTimer = 0.5f;
			myState = Attack;
		}

		if (Target != NULL)
		{
			myDirection = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
			myXSpeed = Math::LenDirX(myMoveSpeed, myDirection);
			myYSpeed = Math::LenDirY(myMoveSpeed, myDirection);

			float distance = Math::PointDistance(myX + myXSpeed, myY + myYSpeed, Target->GetX(), Target->GetY());
			if (distance <= 17)
			{
				myXSpeed = 0;
				myYSpeed = 0;
			}

			
			if (LineEdgeCollision(Vector2f(myX, myY), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
			{
				myState = PathFind;
				FindPath(Target->GetX(), Target->GetY());
			}
		}

		CollisionEntity* brick = ObjCollision(myX, myY, "Enemy");
		if (brick != NULL)
		{
			myDirection = Math::PointDirection(myX, myY, brick->GetX(), brick->GetY());
			myXSpeed += Math::LenDirX(-1.0f, myDirection);
			myYSpeed += Math::LenDirY(-1.0f, myDirection);
		}

		PreventCollision("Brick");
		Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);
	}
}

void ProjectileEnemy::StateAttack()
{
	if (myState == Attack)
	{
		myAttackTimer -= 1.0f / 60.0f;
		if (myAttackTimer <= 0)
		{
			myDirection = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY()) - Math::DegToRad(Math::IRand(-5,5) * Math::IRand(0,1));
			new Projectile(myX, myY, 7.0f, myDirection, false);

			myState = Aggro;
			myAttackTimer = Math::FRand(2, 5);
		}

		Move(myXKnockBack,myYKnockBack);
	}
}

void ProjectileEnemy::Update()
{
	myDepth = myY;
	myColor = sf::Color::White;

	StatePathFind();
	StateAggro();
	StateAttack();
	StateGrabbable();
	StateGrabbed();
	StateThrown();

	PlayerAttack* pAttack = (PlayerAttack*)ObjCollision(myX, myY, "PlayerAttack");

	if (myState != Grabbable and myState != Grabbed and myState != InUse)
	{
		if (pAttack != NULL and myAttackPtr != pAttack)
		{
			float dir = Math::PointDirection(myX, myY, Target->GetX(), Target->GetY());
			myXKnockBack = Math::LenDirX(-19.0f, dir);
			myYKnockBack = Math::LenDirY(-19.0f, dir);
			myXSpeed = 0;
			myYSpeed = 0;
			myHP -= pAttack->GetDamage();
			if (myState == PathFind)
			{
				myState = Aggro;
			}
		}
		myAttackPtr = pAttack;
	}

	if (myHP <= 0 and Alive())
	{
		myState = Grabbable;
	}

	
	myXKnockBack = Math::Lerp(myXKnockBack, 0, 0.25f);
	myYKnockBack = Math::Lerp(myYKnockBack, 0, 0.25f);
}

void ProjectileEnemy::Draw()
{	
	if (Target != NULL)
	{
		if (LineEdgeCollision(Vector2f(myX, myY), Vector2f(Target->GetX(), Target->GetY()), "Solid"))
		{
			myLine.DrawLinePos(myX, myY - myZ, Target->GetX(), Target->GetY(), myDepth - 3, sf::Color::Red);
		}
		else
		{
			myLine.DrawLinePos(myX, myY - myZ, Target->GetX(), Target->GetY(), myDepth - 3, sf::Color::White);
		}
	}

	if (myState != Grabbed)
	{
		if (Alive())
		{
			DrawShadow(myX, myY + myZ, 1.35f + myZ / 100.0f, 0.8f + myZ / 100.0f);
		}
		else
		{
			DrawShadow(myX, myY + myZ + GetHeight() / 2, 1.35f + myZ / 100.0f, 0.8f + myZ / 100.0f);
		}
	}

	CollisionEntity::Draw();
	DrawBBox();

	//rip drawing multiple lines because of my and SFMLs bad design
	for (int i = 0; i < myPath.Size(); i++)
	{
		myLine.DrawLinePos(myPath[i]->GetCenter().x, myPath[i]->GetCenter().y, myPath[i]->GetParent()->GetCenter().x, myPath[i]->GetParent()->GetCenter().y,
			myDepth, sf::Color::White);
	}
}

void ProjectileEnemy::DrawGUI()
{
	DrawFont(std::to_string((int)myHP), myX, myY - 20, 24, 1, 1, sf::Color::White);
	//DrawFont(std::to_string(myZ), myX, myY - 40, 24, 1, 1, sf::Color::White);
}
