#include "stdafx.h"
#include "GSprite.h"

sf::RenderWindow* GSprite::Window;
std::map<std::string, std::pair<sf::Texture*, sf::Sprite*>*> GSprite::SpriteList;
Camera* GSprite::Camera;

GSprite::GSprite()
{
	myWidth = 0;
	myHeight = 0;
	myTextureHeight = 0;
	myTextureWidth = 0;

	myNrOfFrames = 1;
	myAnimationCounter = 0;
	myAnimationSpeed = 0;
	myAnimationIndex = 0;
}

GSprite::~GSprite()
{
}

void GSprite::DeleteAllSprites()
{
	for (auto const &instance : SpriteList)
	{
		delete instance.second->first;
		delete instance.second->second;
		delete instance.second;
	}
}

void GSprite::Draw(float aX, float aY, float aXScale, float aYScale, float aAngle, float aAlpha, sf::Color aColor, float aAnimationSpeed)
{

	myAnimationSpeed = aAnimationSpeed;
	if (myAnimationSpeed > 0)
	{
		myAnimationCounter += myAnimationSpeed;
		if (myAnimationCounter >= 1)
		{
			myAnimationIndex++;
			myAnimationCounter--;
			if (myAnimationIndex >= myNrOfFrames)
			{
				myAnimationIndex = 0;
			}
		}
	}

	mySprite->setTextureRect(sf::IntRect(myAnimationIndex * myTextureWidth / myNrOfFrames, 0, myTextureWidth / myNrOfFrames, myTextureHeight));
	mySprite->setPosition(aX, aY);
	mySprite->setOrigin(myTextureWidth / myNrOfFrames / 2, myTextureHeight / 2);
	mySprite->setRotation(aAngle);
	mySprite->setScale(aXScale, aYScale);

	mySprite->setColor(sf::Color(aColor.r, aColor.g, aColor.b, aAlpha * 255));

	myWidth = myTextureWidth * aXScale;
	myHeight = myTextureHeight * aYScale;
		
	Window->draw(*mySprite);
	
}

void GSprite::DrawOrigin(float aX, float aY, float aOriginX, float aOriginY, float aXScale, float aYScale, float aAngle, float aAlpha, sf::Color aColor, float aAnimationSpeed)
{
	myAnimationSpeed = aAnimationSpeed;
	if (myAnimationSpeed > 0)
	{
		myAnimationCounter += myAnimationSpeed;
		if (myAnimationCounter >= 1)
		{
			myAnimationIndex++;
			myAnimationCounter--;
			if (myAnimationIndex >= myNrOfFrames)
			{
				myAnimationIndex = 0;
			}
		}
	}

	mySprite->setTextureRect(sf::IntRect(myAnimationIndex * myTextureWidth / myNrOfFrames, 0, myTextureWidth / myNrOfFrames, myTextureHeight));
	mySprite->setPosition(aX, aY);
	mySprite->setOrigin(aOriginX, aOriginY);
	mySprite->setRotation(aAngle);
	mySprite->setScale(aXScale, aYScale);

	mySprite->setColor(sf::Color(aColor.r, aColor.g, aColor.b, aAlpha * 255.0f));

	myWidth = myTextureWidth * aXScale;
	myHeight = myTextureHeight * aYScale;

	Window->draw(*mySprite);
}

void GSprite::DrawGUI(float aX, float aY, float aXScale, float aYScale, float aAngle, float aAlpha, sf::Color aColor, float aAnimationSpeed)
{
	myAnimationSpeed = aAnimationSpeed;
	if (myAnimationSpeed > 0)
	{
		myAnimationCounter += myAnimationSpeed;
		if (myAnimationCounter >= 1)
		{
			myAnimationIndex++;
			myAnimationCounter--;
			if (myAnimationIndex >= myNrOfFrames)
			{
				myAnimationIndex = 0;
			}
		}
	}

	mySprite->setTextureRect(sf::IntRect(myAnimationIndex * myTextureWidth / myNrOfFrames, 0, myTextureWidth / myNrOfFrames, myTextureHeight));
	mySprite->setPosition(aX + Camera->GetX() - Camera->GetViewWidth() /2, aY + Camera->GetY() - Camera->GetViewHeight() / 2);
	mySprite->setOrigin(myTextureWidth / myNrOfFrames / 2, myTextureHeight / 2);
	mySprite->setRotation(aAngle);
	mySprite->setScale(aXScale, aYScale);

	mySprite->setColor(sf::Color(aColor.r, aColor.g, aColor.b, aAlpha * 255));
	myWidth = myTextureWidth * aXScale;
	myHeight = myTextureHeight * aYScale;

	Window->draw(*mySprite);
}

//Accessors
float GSprite::GetTextureWidth()
{
	return myTextureWidth;
}

float GSprite::GetTextureHeight()
{
	return myTextureHeight;
}

int GSprite::GetAnimationIndex() const
{
	return myAnimationIndex;
}

int GSprite::GetNrOfFrames() const
{
	return myNrOfFrames;
}

int GSprite::GetAnimationCounter() const
{
	return myAnimationCounter;
}

//Modifiers
void GSprite::SetTexture(std::string aFileName, int aNrOfFrames)
{
	if (SpriteList.count(aFileName) == 0)
	{
		SpriteList[aFileName] = new std::pair<sf::Texture*, sf::Sprite*>;
		SpriteList[aFileName]->first = new sf::Texture();
		SpriteList[aFileName]->second = new sf::Sprite();
		myTexture = SpriteList[aFileName]->first;
		mySprite = SpriteList[aFileName]->second;

		if (!myTexture->loadFromFile(aFileName)) { throw "file not found"; }
		myTexture->setSmooth(false);
		mySprite->setTexture(*myTexture);
	}
	else
	{
		myTexture = SpriteList[aFileName]->first;
		mySprite = SpriteList[aFileName]->second;
	}

	myNrOfFrames = aNrOfFrames;
	myTextureWidth = myTexture->getSize().x;
	myTextureHeight = myTexture->getSize().y;
}

void GSprite::SetAnimationIndex(int aIndex)
{
	myAnimationIndex = aIndex;
}

void GSprite::SetAnimationSpeed(float aSpeed)
{
	myAnimationSpeed = aSpeed;
}