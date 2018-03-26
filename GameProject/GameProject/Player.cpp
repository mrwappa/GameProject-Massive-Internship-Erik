#include "stdafx.h"
#include "Player.h"

#include "Brick.h"
Player::Player(float aX, float aY)
{
	CollisionEntity::Init("Player",aX,aY);
	
	myX = aX;
	myY = aY;

	myCharTextures[(int)Back].loadFromFile("Sprites/Player/spr_player_back.png");
	myCharTextures[(int)BackLeft].loadFromFile("Sprites/Player/spr_player_back_left.png");
	myCharTextures[(int)Front].loadFromFile("Sprites/Player/spr_player_front.png");
	myCharTextures[(int)FrontLeft].loadFromFile("Sprites/Player/spr_player_front_left.png");
	myCharTextures[(int)Left].loadFromFile("Sprites/Player/spr_player_left.png");

	mySprite.SetTexture(myCharTextures[(int)Front], 3);

	myAnimationSpeed = 0.f;
	myXScale = 2.0f;
	myYScale = myXScale;

	myMovementSpeed = 4.5f;
	myXSpeedMax = myMovementSpeed;
	myYSpeedMax = myMovementSpeed;

	myXAcceleration = 0.7f;
	myYAcceleration = 0.7f;
	myXRestitution = 0.5f;
	myYRestitution = 0.5f;

	myBoxWidth = 20;
	myBoxHeight = 20;
}


Player::~Player()
{

}

void Player::Update()
{
	
	myLookAngle = Math::PointDirection(myX, myY, Camera->GetMouseX(), Camera->GetMouseY());
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

	CollisionEntity* brick = ObjCollision(myX + myXSpeed,myY,"Solid");
	
	//X Axis Collision
	if (InstanceCollision(myX + myXSpeed, myY, brick))
	{
		float brickBoxWidth = brick->GetBounds().GetWidth();
		float brickBoxX = brick->GetBoxPosition().x + brickBoxWidth / 2;

		if (myX > brickBoxX and myXSpeed < 0)
		{
			myX = brickBoxX + (brickBoxWidth / 2) + (myBoundingBox.GetWidth() / 2);
		}
		if (myX < brickBoxX and myXSpeed > 0)
		{
			myX = brickBoxX - (brickBoxWidth / 2) - (myBoundingBox.GetWidth() / 2);
		}
		myXSpeed = 0;
	}

	brick = ObjCollision(myX, myY + myYSpeed, "Solid");

	//Y Axis Collision
	if (InstanceCollision(myX, myY + myYSpeed, brick))
	{
		float brickBoxHeight = brick->GetBounds().GetHeight();
		float brickBoxY = brick->GetBoxPosition().y + brickBoxHeight / 2;

		if (myY > brickBoxY and myYSpeed < 0)
		{
			myY = brickBoxY + (brickBoxHeight / 2) + (myBoundingBox.GetWidth() / 2);
		}
		if (myY < brickBoxY and myYSpeed > 0)
		{
			myY = brickBoxY - (brickBoxHeight / 2) - (myBoundingBox.GetWidth() / 2);
		}
		myYSpeed = 0;
	}
	
	

	myX += myXSpeed;
	myY += myYSpeed;

	if (MouseWheelDown())
	{
		Camera->IncrZoom(-0.095f * Camera->GetZoom());
	}
	if (MouseWheelUp())
	{
		Camera->IncrZoom(0.095f * Camera->GetZoom());
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
	Entity::Draw();
	DrawBBox();
	
	
}

void Player::DrawGUI()
{
	
}

void Player::TextureDirection(float aAngle)
{
	if (aAngle < 25 && aAngle > 0 || aAngle > -25 && aAngle < 0)
	{
		//Right
		mySprite.SetTexture(myCharTextures[(int)Left],3);
		myXScale = -2;
	}
	if (aAngle < -25 && aAngle > -70)
	{
		//Back Right
		mySprite.SetTexture(myCharTextures[(int)BackLeft], 3);
		myXScale = -2;
	}
	if (aAngle < -70 && aAngle > -115)
	{
		//Back
		mySprite.SetTexture(myCharTextures[(int)Back], 3);
		myXScale = 2;
	}
	if (aAngle < -115 && aAngle > -160)
	{
		//Back Left
		mySprite.SetTexture(myCharTextures[(int)BackLeft], 3);
		myXScale = 2;
	}
	if (aAngle < -160 && aAngle > -180 || aAngle > 155 && aAngle < 180)
	{
		//Left
		mySprite.SetTexture(myCharTextures[(int)Left], 3);
		myXScale = 2;
	}
	if (aAngle < 155 && aAngle > 110)
	{
		//Front Left
		mySprite.SetTexture(myCharTextures[(int)FrontLeft], 3);
		myXScale = 2;
	}
	if (aAngle < 110 && aAngle > 65)
	{
		//Front
		mySprite.SetTexture(myCharTextures[(int)Front], 3);
		myXScale = 2;
	}
	if (aAngle < 65 && aAngle > 25)
	{
		//Front Right
		mySprite.SetTexture(myCharTextures[(int)FrontLeft], 3);
		myXScale = -2;
	}
}

