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
	myXScale = 2;
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

	CollisionEntity* brick = (CollisionEntity*)GetObj("Brick");

	if (myAngle == 0 or myAngle == 180)
	{
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
	}
	else
	{
		if (InstanceCollision(myX + myXSpeed, myY, brick))
		{
			for (int i = 0; i < abs(myXSpeed); i++)
			{
				if (InstanceCollision(myX + Math::Sign(myXSpeed), myY, brick)) { break; }
				myX += Math::Sign(myXSpeed);
			}
			myXSpeed = 0;
			/*float brickBoxWidth = brick->GetBounds().GetWidth();
			float brickBoxX = brick->GetBoxPosition().x + brickBoxWidth / 2;

			if (myX > brickBoxX and myXSpeed < 0)
			{
				myX = brickBoxX + (brickBoxWidth / 2);
			}
			if (myX < brickBoxX and myXSpeed > 0)
			{
				myX = brickBoxX - (brickBoxWidth / 2);
			}

			int diameter = myBoxWidth > myBoxHeight ? myBoxWidth * myXScale : myBoxHeight * myYScale;
			for (int i = 0; i < diameter; i++)
			{
				
				if (!InstanceCollision(myX, myY, brick))
				{
					break;
				}
				myX -= Math::Sign(myXSpeed);
			}

			myXSpeed = 0;*/
		}

		if (InstanceCollision(myX, myY + myYSpeed, brick))
		{
			for (int i = 0; i < abs(myYSpeed); i++)
			{
				if (InstanceCollision(myX, myY + Math::Sign(myYSpeed), brick)) { break; }
				myY += Math::Sign(myYSpeed);
			}
			myYSpeed = 0;
			/*float brickBoxHeight = brick->GetBounds().GetHeight();
			float brickBoxY = brick->GetBoxPosition().y + brickBoxHeight / 2;

			if (myY > brickBoxY and myYSpeed < 0)
			{
				myY = brickBoxY + (brickBoxHeight / 2);
			}
			if (myY < brickBoxY and myYSpeed > 0)
			{
				myY = brickBoxY - (brickBoxHeight / 2);
			}

			int diameter = myBoxWidth > myBoxHeight ? myBoxWidth * myXScale : myBoxHeight * myYScale;

			for (int i = 0; i < diameter; i++)
			{
				
				if (!InstanceCollision(myX, myY, brick))
				{
					break;
				}
				myY -= Math::Sign(myYSpeed);
			}

			myYSpeed = 0;*/
		}
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

