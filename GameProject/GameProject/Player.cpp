#include "stdafx.h"
#include "Player.h"


Player::Player(float aX, float aY) : Entity("Player")
{
	myX = aX;
	myY = aY;
	myGUISprite.SetTexture("Sprites/spr_link_sheet.png", 9);
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

	/*Camera->SetX(myX);
	Camera->SetY(myY);*/
}

void Player::Draw()
{
	Entity::Draw();
	myGUISprite.DrawGUI(100,100,1,1,0,1,sf::Color::White,0);
}

void Player::DrawGUI()
{
	
}

