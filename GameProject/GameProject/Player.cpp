#include "stdafx.h"
#include "Player.h"


Player::Player(float aX, float aY, sf::Color aColor) : Entity("Player")
{
	myX = aX;
	myY = aY;
	myColor = aColor;

	mySprite.SetTexture("Sprites/spr_link_sheet.png", 9);
	myAnimationSpeed = 0.3f;
	myXScale = 2;
	myYScale = myXScale;
}


Player::~Player()
{

}

void Player::Update()
{

	if (KeyboardCheckPressed(sf::Keyboard::O) or KeyboardCheckPressed(sf::Keyboard::I))
	{
		myDepth += 0.1f;
	}
	if (KeyboardCheckPressed(sf::Keyboard::K) or KeyboardCheckPressed(sf::Keyboard::L))
	{
		myDepth -= 0.1f;
	}
	if (KeyboardCheck(sf::Keyboard::S))
	{
		myY += 1;
	}

}

void Player::Draw()
{
	Entity::Draw();
}