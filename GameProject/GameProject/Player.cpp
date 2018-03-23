#include "stdafx.h"
#include "Player.h"

#include "Brick.h"
Player::Player(float aX, float aY)
{
	Entity::Init("Player",aX,aY);
	
	myX = aX;
	myY = aY;
	mySprite.SetTexture("Sprites/spr_link_sheet.png", 9);
	myAnimationSpeed = 0.3f;
	myXScale = 1;
	myYScale = myXScale;

	myMovementSpeed = 2.5f;
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

	myX += myXSpeed;
	myY += myYSpeed;

	if (KeyboardCheck(sf::Keyboard::T))
	{
		myAngle += 2;
	}
	if (KeyboardCheck(sf::Keyboard::G))
	{
		myAngle -= 2;
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
	/*Camera->SetX(myX);
	Camera->SetY(myY);*/
}

void Player::Draw()
{
	Entity::Draw();
	DrawBBox();
}

void Player::DrawGUI()
{
	
}

