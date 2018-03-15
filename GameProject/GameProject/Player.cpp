#include "stdafx.h"
#include "Player.h"


Player::Player(float aX, float aY) : Entity("Player")
{
	myX = aX;
	myY = aY;

	mySprite.SetTexture("Sprites/spr_link_sheet.png", 9);
	myAnimationSpeed = 0.3f;
	myXScale = 1;
	myYScale = myXScale;
}


Player::~Player()
{

}

void Player::Update()
{
	if (myColor == sf::Color::Red)
	{
		if (KeyboardCheckPressed(sf::Keyboard::O))
		{
			myDepth += 1;
		}

		if (KeyboardCheckPressed(sf::Keyboard::L))
		{
			myDepth -= 1;
		}
	}

	if (myColor == sf::Color::White)
	{
		if (KeyboardCheckPressed(sf::Keyboard::I))
		{
			myDepth += 1;
		}
		if (KeyboardCheckPressed(sf::Keyboard::K))
		{
			myDepth -= 1;
		}
	}

	if (KeyboardCheck(sf::Keyboard::W))
	{
		myY -= 1;
	}
	if (KeyboardCheck(sf::Keyboard::A))
	{
		myX -= 1;
	}
	if (KeyboardCheck(sf::Keyboard::S))
	{
		myY += 1;
	}
	if (KeyboardCheck(sf::Keyboard::D))
	{
		myX += 1;
	}

	

}

void Player::Draw()
{
	Entity::Draw();
}