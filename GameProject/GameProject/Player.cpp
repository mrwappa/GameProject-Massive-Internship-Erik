#include "stdafx.h"
#include "Player.h"

#include "PlayerAttack.h"

Player::Player(float aX, float aY)
{
	Init("Player",aX,aY);
	
	Enemy::Target = this;

	myX = aX;
	myY = aY;

	myShadow.SetTexture("Sprites/Player/spr_circle.png",1);
	
	myCharTextures[Back] = ("Sprites/Player/spr_player_back.png");
	myCharTextures[BackLeft] = ("Sprites/Player/spr_player_back_left.png");
	myCharTextures[Front] = ("Sprites/Player/spr_player_front.png");
	myCharTextures[FrontLeft] = ("Sprites/Player/spr_player_front_left.png");
	myCharTextures[Left] = ("Sprites/Player/spr_player_left.png");
	
	mySprite.SetTexture(myCharTextures[Front], 3);

	myXScale = 2.0f;
	myYScale = myXScale;

	myMoveSpeed = 4.5f;
	myXSpeedMax = myMoveSpeed;
	myYSpeedMax = myMoveSpeed;

	myXAcceleration = 0.7f;
	myYAcceleration = 0.7f;
	myXRestitution = 1.f;
	myYRestitution = 1.f;

	myBoxWidth = 13;
	myBoxHeight = 11;

	myBoxYOffset = 3;

	myPreviousAIndex = 0;

	myHP = 10;
	myAttackTimer = 0.f;
	myDamage = 4;
}


Player::~Player()
{

}

void Player::Update()
{
	
}

void Player::BeginUpdate()
{
	if (Enemy::Target == NULL)
	{
		Enemy::Target = this;
	}
	myLookAngle = Math::PointDirDeg(myX, myY, Camera->GetMouseX(), Camera->GetMouseY());
	TextureDirection(myLookAngle);
	myDepth = myY;

	//Check keys
	W = KeyboardCheck(sf::Keyboard::W);
	A = KeyboardCheck(sf::Keyboard::A);
	S = KeyboardCheck(sf::Keyboard::S);
	D = KeyboardCheck(sf::Keyboard::D);

	//Direction by keys
	myXDir = D - A;
	myYDir = S - W;

	//Acceleration
	myXAdd = myXDir * myXAcceleration;
	myYAdd = myYDir * myYAcceleration;

	//Restitution
	myXSub = std::min(myXRestitution, std::abs(myXSpeed)) * Math::Sign(myXSpeed) * (myXDir == 0);
	myYSub = std::min(myYRestitution, std::abs(myYSpeed)) * Math::Sign(myYSpeed) * (myYDir == 0);

	myXSpeed = Math::Clamp(myXSpeed + myXAdd - myXSub, -myMoveSpeed, myMoveSpeed);
	myYSpeed = Math::Clamp(myYSpeed + myYAdd - myYSub, -myMoveSpeed, myMoveSpeed);

	//Diagonals
	if (myXSpeed != 0 and myYSpeed != 0)
	{
		float dist = Math::SQRT2((myXSpeed * myXSpeed) + (myYSpeed * myYSpeed));
		float mdist = std::min(myMoveSpeed, dist);
		myXSpeed = (myXSpeed / dist) * mdist;
		myYSpeed = (myYSpeed / dist) * mdist;
	}


	Enemy* enemy = (Enemy*)ObjCollision(myX, myY, "Enemy");
	Projectile* projectile = (Projectile*)ObjCollision(myX, myY, "Projectile");
	if (myHurtAlarm.GetTick() == -1)
	{
		if (projectile != NULL and !projectile->GetEnemyThreat())
		{
			myDirection = Math::PointDirection(projectile->GetX(), projectile->GetY(), myX, myY);
			myXKnockBack = Math::LenDirX(10, myDirection);
			myYKnockBack = Math::LenDirY(10, myDirection);

			myHP -= projectile->GetDamage();
			myHurtAlarm.SetTick(20);

			DeleteInstance(projectile);
		}
		if (enemy != NULL and enemy->Alive() and enemy->GetDamage() > 0)
		{
			myDirection = Math::PointDirection(enemy->GetX(), enemy->GetY() - enemy->GetZ(), myX, myY);
			myXKnockBack = Math::LenDirX(15, myDirection);
			myYKnockBack = Math::LenDirY(15, myDirection);

			myHP -= enemy->GetDamage();
			myHurtAlarm.SetTick(25);
		}
	}
	

	myXKnockBack = Math::Lerp(myXKnockBack, 0, 0.3f);
	myYKnockBack = Math::Lerp(myYKnockBack, 0, 0.3f);

	PreventCollision("Solid");
	Move(myXSpeed + myXKnockBack, myYSpeed + myYKnockBack);

	//Sprite Animation Speed
	float trueXSpeed = abs(myX - myPreviousX);
	float trueYSpeed = abs(myY - myPreviousY);
	if (myXSpeed != 0 and myYSpeed != 0)
	{
		myAnimationSpeed = abs(trueYSpeed + trueXSpeed) / 59.0f;
	}
	else
	{
		myAnimationSpeed = abs(trueYSpeed + trueXSpeed) / 45.0f;
	}
	if (myAnimationSpeed == 0)
	{
		mySprite.SetAnimationIndex(0);
	}

	//Dust Effect
	if (mySprite.GetAnimationIndex() == mySprite.GetNrOfFrames() - 1 and myPreviousAIndex != mySprite.GetNrOfFrames() - 1)
	{
		new Dust(myX, myY + 20, Math::PointDirDeg(0, 0, myXSpeed, myYSpeed) - 270);
	}
	

	if (myHurtAlarm.GetTick() != -1)
	{
		myColor = sf::Color::Color(Math::IRand(0,255 - myAttackTimer * 255), Math::IRand(0, 255 - myAttackTimer * 255), Math::IRand(0, 255 - myAttackTimer * 255));
	}
	else
	{
		myColor = sf::Color::Color(255 - myAttackTimer * 255, 255 - myAttackTimer * 255, 255 - myAttackTimer * 255);
	}
	
	//Camera Stuff
	if (MouseWheelDown())
	{
		Camera->IncrZoom(-0.095f * Camera->GetZoom());
	}
	if (MouseWheelUp())
	{
		Camera->IncrZoom(0.095f * Camera->GetZoom());
	}

	Camera->SetX(myX);
	Camera->SetY(myY);
}

void Player::EndUpdate()
{
	bool grabbedThisFrame = false;
	//Enemy as weapon
	if (GrabbableEnemy == NULL)
	{
		Enemy* enemy = NearestGrabbable();
		if (enemy != NULL)
		{
			if (Math::PointDistance(myX, myY, enemy->GetX(), enemy->GetY()) < 80 and enemy->GetState() == Enemy::Grabbable)
			{
				enemy->SetColor(Enemy::GrabColor);
				if (KeyboardCheckPressed(sf::Keyboard::LShift))
				{
					GrabbableEnemy = enemy;
					GrabbableEnemy->SetState(Enemy::Grabbed);
					grabbedThisFrame = true;
				}
			}
		}
	}

	//Enemy as attack
	if (GrabbableEnemy != NULL)
	{
		//Throw
		if (KeyboardCheckPressed(sf::Keyboard::Space))
		{
			GrabbableEnemy->Throw(28, Math::PointDirection(myX, myY, Camera->GetMouseX(), Camera->GetMouseY()));
			GrabbableEnemy = NULL;
		}
		//Drop
		if (KeyboardCheckPressed(sf::Keyboard::LShift) and GrabbableEnemy != NULL and !grabbedThisFrame)
		{
			GrabbableEnemy->SetState(Enemy::Grabbable);
			GrabbableEnemy->SetZ(15);
			GrabbableEnemy = NULL;
		}
		//Attack
		if (MouseCheckPressed(sf::Mouse::Left) and GrabbableEnemy != NULL and GrabbableEnemy->GetState() == Enemy::Grabbed)
		{
			//unnescessary check right now, but will be relevent when more enemies appear
			if (GrabbableEnemy->GetName() == "TestEnemy")
			{
				GrabbableEnemy->SetZ(GrabbableEnemy->GetHeight() / 1.5f);
				GrabbableEnemy->SetDirection(Math::PointDirection(myX, myY, Camera->GetMouseX(), Camera->GetMouseY()));
				GrabbableEnemy->SetState(Enemy::InUse);
			}
			else
			{
				GrabbableEnemy->SetState(Enemy::InUse);
			}
		}
	}

	//Default Attack
	myAttackTimer -= 1.0f / 60.0f;
	if (myAttackTimer <= 0)
	{
		myAttackTimer = 0;
	}

	if (myHurtAlarm.GetTick() == -1)
	{
		if (GrabbableEnemy == NULL)
		{
			if (MouseCheckPressed(sf::Mouse::Left) and PAttack == NULL and myAttackTimer <= 0)
			{
				myAttackTimer = 0.4f;
				PAttack = new PlayerAttack(myX, myY, this);
			}

			if (PAttack != NULL)
			{
				myDirection = Math::PointDirection(myX, myY, Camera->GetMouseX(), Camera->GetMouseY());
				float atX = myX + Math::LenDirX(18, myDirection);
				float atY = myY + Math::LenDirY(18, myDirection);

				PAttack->SetX(atX);
				PAttack->SetY(atY);
				PAttack->SetAngle(Math::RadToDeg(myDirection));
				PAttack->SetXOffset(Math::LenDirX(18, myDirection));
				PAttack->SetYOffset(Math::LenDirY(18, myDirection));
			}
		}
	}
	
}

void Player::Draw()
{
	myPreviousAIndex = mySprite.GetAnimationIndex();
	if (mySprite.GetAnimationIndex() == 2)
	{
		myShadow.Draw(myX, myY + 16, 1.5f, 1.2f, 0, 0.6f, sf::Color::Black, 0);
	}
	else
	{
		myShadow.Draw(myX, myY + 18, 1.5f, 1.2f, 0, 0.6f, sf::Color::Black, 0);
	}
	
	CollisionEntity::Draw();
	//DrawBBox();

	
}

void Player::DrawGUI()
{
	//DrawFontGUI(std::to_string(myX) +  " " + std::to_string(myY), 0, 0, 24, 1, 1, sf::Color::White);
	DrawFontGUI("Solid:" + std::to_string(CollisionList.at("Solid")->Size()), 700, 200, 24, 1, 1, sf::Color::White);
	/*DrawFontGUI("Brick:" + std::to_string(SuperList.at("Brick")->Size()), 0, 40, 24, 1, 1, sf::Color::White);
	DrawFontGUI("Player:" + std::to_string(SuperList.at("Player")->Size()), 0, 80, 24, 1, 1, sf::Color::White);
	DrawFontGUI("TestEnemy:" + std::to_string(SuperList.at("TestEnemy")->Size()), 0, 120, 24, 1, 1, sf::Color::White);
	DrawFontGUI("World:" + std::to_string(SuperList.at("World")->Size()), 0, 160, 24, 1, 1, sf::Color::White);

	DrawFontGUI("Brick:" + std::to_string(CollisionList.at("Brick")->Size()), 700, 40, 24, 1, 1, sf::Color::White);
	DrawFontGUI("Player:" + std::to_string(CollisionList.at("Player")->Size()), 700, 80, 24, 1, 1, sf::Color::White);
	DrawFontGUI("TestEnemy:" + std::to_string(CollisionList.at("TestEnemy")->Size()), 700, 120, 24, 1, 1, sf::Color::White);
	DrawFontGUI("Enemy:" + std::to_string(CollisionList.at("Enemy")->Size()), 700, 160, 24, 1, 1, sf::Color::White);
	DrawFontGUI("Solid:" + std::to_string(CollisionList.at("Solid")->Size()), 700, 200, 24, 1, 1, sf::Color::White);

	DrawFontGUI("DeleteMarkedList:" + std::to_string(DeleteMarkedList.Size()), 540, 280, 24, 1, 1, sf::Color::White);*/
}

void Player::OnRemoval()
{
	Enemy::Target = NULL;
	CollisionEntity::OnRemoval();
}

Enemy * Player::NearestGrabbable()
{

	if (CollisionList.count("Enemy") == 0)
	{
		return NULL;
	}
	int nearestLength = -1;
	CollisionEntity* colInstance = NULL;

	GrowingArray<CollisionEntity*>* GrArrayPtr = CollisionList.at("Enemy");

	for (int i = 0; i < GrArrayPtr->Size(); i++)
	{
		Enemy* currentInstance = (Enemy*)GrArrayPtr->FindAtIndex(i);
		if (currentInstance->GetState() == Enemy::Grabbable)
		{
			int instanceLength = Math::PointDistance(myX, myY, currentInstance->GetX(), currentInstance->GetY());
			if (nearestLength == -1)
			{
				nearestLength = instanceLength;
				colInstance = currentInstance;
			}
			else if (instanceLength < nearestLength and nearestLength != -1)
			{
				nearestLength = instanceLength;
				colInstance = currentInstance;
			}
		}
	}

	return (Enemy*)colInstance;
}

void Player::TextureDirection(float aAngle)
{
	if (aAngle < 25 and aAngle > 0 || aAngle > -25 and aAngle < 0)
	{
		//Right
		mySprite.SetTexture(myCharTextures[Left],3);
		myXScale = -2;
	}
	if (aAngle < -25 and aAngle > -70)
	{
		//Back Right
		mySprite.SetTexture(myCharTextures[BackLeft], 3);
		myXScale = -2;
	}
	if (aAngle < -70 and aAngle > -115)
	{
		//Back
		mySprite.SetTexture(myCharTextures[Back], 3);
		myXScale = 2;
	}
	if (aAngle < -115 and aAngle > -160)
	{
		//Back Left
		mySprite.SetTexture(myCharTextures[BackLeft], 3);
		myXScale = 2;
	}
	if (aAngle < -160 and aAngle > -180 || aAngle > 155 and aAngle < 180)
	{
		//Left
		mySprite.SetTexture(myCharTextures[Left], 3);
		myXScale = 2;
	}
	if (aAngle < 155 and aAngle > 110)
	{
		//Front Left
		mySprite.SetTexture(myCharTextures[FrontLeft], 3);
		myXScale = 2;
	}
	if (aAngle < 110 and aAngle > 65)
	{
		//Front
		mySprite.SetTexture(myCharTextures[Front], 3);
		myXScale = 2;
	}
	if (aAngle < 65 and aAngle > 25)
	{
		//Front Right
		mySprite.SetTexture(myCharTextures[FrontLeft], 3);
		myXScale = -2;
	}
}

