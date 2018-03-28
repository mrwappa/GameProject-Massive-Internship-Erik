#include "stdafx.h"
#include "Player.h"

#include "Brick.h"
Player::Player(float aX, float aY)
{
	Enemy::Target = this;

	Init("Player",aX,aY);
	
	myX = aX;
	myY = aY;

	myShadow[0] = new GSprite();
	myShadow[0]->SetTexture("Sprites/Player/spr_circle.png",1);

	for (int i = 0; i < T_SIZE; i++)
	{
		myCharTextures[i] = new sf::Texture();
	}
	
	myCharTextures[Back]->loadFromFile("Sprites/Player/spr_player_back.png");
	myCharTextures[BackLeft]->loadFromFile("Sprites/Player/spr_player_back_left.png");
	myCharTextures[Front]->loadFromFile("Sprites/Player/spr_player_front.png");
	myCharTextures[FrontLeft]->loadFromFile("Sprites/Player/spr_player_front_left.png");
	myCharTextures[Left]->loadFromFile("Sprites/Player/spr_player_left.png");
	
	mySprite.SetTexture(*myCharTextures[Front], 3);

	myXScale = 2.0f;
	myYScale = myXScale;

	myMovementSpeed = 4.5f;
	myXSpeedMax = myMovementSpeed;
	myYSpeedMax = myMovementSpeed;

	myXAcceleration = 0.7f;
	myYAcceleration = 0.7f;
	myXRestitution = 1.f;
	myYRestitution = 1.f;

	myBoxWidth = 13;
	myBoxHeight = 11;

	myBoxYOffset = 3;

	myPreviousAIndex = 0;
}


Player::~Player()
{

}

void Player::Update()
{
	myLookAngle = Math::PointDirDeg(myX, myY, Camera->GetMouseX(), Camera->GetMouseY());
	TextureDirection(myLookAngle);
	myDepth = -myY;

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

	myXSpeed = Math::Clamp(myXSpeed + myXAdd - myXSub, -myMovementSpeed, myMovementSpeed);
	myYSpeed = Math::Clamp(myYSpeed + myYAdd - myYSub, -myMovementSpeed, myMovementSpeed);

	//Diagonals
	if (myXSpeed != 0 and myYSpeed != 0)
	{
		float dist = Math::SQRT2((myXSpeed * myXSpeed) + (myYSpeed * myYSpeed));
		float mdist = std::min(myMovementSpeed, dist);
		myXSpeed = (myXSpeed / dist) * mdist;
		myYSpeed = (myYSpeed / dist) * mdist;
	}

	CollisionEntity* brick = ObjCollision(myX + myXSpeed,myY,"Brick");
	
	//X Axis Collision
	if (brick != NULL)
	{
		float brickBoxX = brick->GetBoxPosition().x;
		myX = floor(myX) + Math::Decimal(brickBoxX);
		for (int i = 0; i < abs(myXSpeed); i++)
		{
			if (InstanceCollision(myX + Math::Sign(myXSpeed), myY, brick)) { break; }
			myX += Math::Sign(myXSpeed);
		}
		myXSpeed = 0;
	}

	brick = ObjCollision(myX, myY + myYSpeed, "Solid");

	//Y Axis Collision
	if (brick != NULL)
	{
		float brickBoxY = brick->GetBoxPosition().y;
		myY = floor(myY) + Math::Decimal(brickBoxY);
		for (int i = 0; i < abs(myYSpeed); i++)
		{
			if (InstanceCollision(myX, myY + Math::Sign(myYSpeed), brick)) { break; }
			myY += Math::Sign(myYSpeed);
		}
		myYSpeed = 0;
	}
	
	Move(myXSpeed, myYSpeed);

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
	
	
	if (mySprite.GetAnimationIndex() == mySprite.GetNrOfFrames() - 1 and myPreviousAIndex != mySprite.GetNrOfFrames() - 1)
	{
		new Dust(myX, myY + 20, Math::PointDirDeg(0, 0, myXSpeed, myYSpeed) - 270);
	}

	if (MouseWheelDown())
	{
		Camera->IncrZoom(-0.095f * Camera->GetZoom());
	}
	if (MouseWheelUp())
	{
		Camera->IncrZoom(0.095f * Camera->GetZoom());
	}
	if (KeyboardCheckPressed(sf::Keyboard::Space))
	{
		Camera->ShakeScreen(6.0f);
	}

	myColor = sf::Color::White;
	if (InstanceCollision(myX, myY, (CollisionEntity*)GetObj("Brick")))
	{
		myColor = sf::Color::Red;
	}
	
	/*if (KeyboardCheckPressed(sf::Keyboard::Tab))
	{
		DeleteInstance(this);
	}*/
	Camera->SetX(myX);
	Camera->SetY(myY);
}

void Player::Draw()
{
	myPreviousAIndex = mySprite.GetAnimationIndex();
	if (mySprite.GetAnimationIndex() == 2)
	{
		myShadow[0]->Draw(myX, myY + 16, 1.5f, 1.2f, 0, myDepth + 1, 0.6f, sf::Color::Black, 0);
	}
	else
	{
		myShadow[0]->Draw(myX, myY + 18, 1.5f, 1.2f, 0, myDepth + 1, 0.6f, sf::Color::Black, 0);
	}
	
	Entity::Draw();
	DrawBBox();
}

void Player::DrawGUI()
{
	GrowingArray<Entity*>* list = SuperList.at("Brick");

	DrawFontGUI(std::to_string(list->Size()), 20, 20, 24, 1, 1, sf::Color::White);
}

void Player::OnRemoval()
{
	for (int i = 0; i < T_SIZE; i++)
	{
		delete myCharTextures[i];
	}
	delete myShadow[0];
	CollisionEntity::OnRemoval();
}

void Player::TextureDirection(float aAngle)
{
	if (aAngle < 25 && aAngle > 0 || aAngle > -25 && aAngle < 0)
	{
		//Right
		mySprite.SetTexture(*myCharTextures[Left],3);
		myXScale = -2;
	}
	if (aAngle < -25 && aAngle > -70)
	{
		//Back Right
		mySprite.SetTexture(*myCharTextures[BackLeft], 3);
		myXScale = -2;
	}
	if (aAngle < -70 && aAngle > -115)
	{
		//Back
		mySprite.SetTexture(*myCharTextures[Back], 3);
		myXScale = 2;
	}
	if (aAngle < -115 && aAngle > -160)
	{
		//Back Left
		mySprite.SetTexture(*myCharTextures[BackLeft], 3);
		myXScale = 2;
	}
	if (aAngle < -160 && aAngle > -180 || aAngle > 155 && aAngle < 180)
	{
		//Left
		mySprite.SetTexture(*myCharTextures[Left], 3);
		myXScale = 2;
	}
	if (aAngle < 155 && aAngle > 110)
	{
		//Front Left
		mySprite.SetTexture(*myCharTextures[FrontLeft], 3);
		myXScale = 2;
	}
	if (aAngle < 110 && aAngle > 65)
	{
		//Front
		mySprite.SetTexture(*myCharTextures[Front], 3);
		myXScale = 2;
	}
	if (aAngle < 65 && aAngle > 25)
	{
		//Front Right
		mySprite.SetTexture(*myCharTextures[FrontLeft], 3);
		myXScale = -2;
	}
}

