#include "stdafx.h"
#include "GSprite.h"

sf::RenderWindow* GSprite::Window;
sf::Shader* GSprite::DepthShader;

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

GSprite::GSprite(sf::Texture aTexture, int aNrOfFrames)
{
	myWidth = 0;
	myHeight = 0;
	myTextureHeight = 0;
	myTextureWidth = 0;

	myNrOfFrames = aNrOfFrames;
	myAnimationCounter = 0;
	myAnimationSpeed = 0;
	myAnimationIndex = 0;

	myTexture = aTexture;
	mySprite.setTexture(myTexture);
	myTextureWidth = myTexture.getSize().x;
	myTextureHeight = myTexture.getSize().y;
}


GSprite::~GSprite()
{
}

void GSprite::Draw(float aX, float aY, float aXScale, float aYScale, float aAngle, float aDepth, float aAlpha, sf::Color aColor, float aAnimationSpeed)
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

	mySprite.setTextureRect(sf::IntRect(myAnimationIndex * myTextureWidth / myNrOfFrames, 0, myTextureWidth / myNrOfFrames, myTextureHeight));
	mySprite.setPosition(aX, aY);
	mySprite.setOrigin(myTextureWidth / myNrOfFrames / 2, myTextureHeight / 2);
	mySprite.setRotation(aAngle);
	mySprite.setScale(aXScale, aYScale);

	mySprite.setColor(sf::Color(aColor.r, aColor.g, aColor.b, aAlpha * 255));

	myWidth = myTextureWidth * aXScale;
	myHeight = myTextureHeight * aYScale;

	//myDepth = -aDepth;
	
	
	/*glPushMatrix();
	Window->resetGLStates();
	glTranslatef(0, 0, aDepth);
	Window->draw(mySprite);
	glPopMatrix();*/
	DepthShader->setUniform("depth",aDepth);
	Window->draw(mySprite, DepthShader);
}

//Accessors
float GSprite::GetDepth()
{
	return myDepth;
}

sf::Sprite GSprite::GetSprite()
{
	return mySprite;
}

sf::Texture GSprite::GetTexture()
{
	return myTexture;
}

float GSprite::GetTextureWidth()
{
	return myTextureWidth;
}

//Modifiers
void GSprite::SetTexture(std::string aFileName, int aNrOfFrames)
{
	if (!myTexture.loadFromFile(aFileName)) { throw "file not found"; }

	mySprite.setTexture(myTexture);
	myTextureWidth = myTexture.getSize().x;
	myTextureHeight = myTexture.getSize().y;

	myNrOfFrames = aNrOfFrames;
}

void GSprite::SetTexture(sf::Texture aTexture, int aNrOfFrames)
{
	myTexture = aTexture;
	mySprite.setTexture(myTexture);
	myTextureWidth = myTexture.getSize().x;
	myTextureHeight = myTexture.getSize().y;
}

void GSprite::SetSprite(sf::Sprite aSprite)
{
	mySprite = aSprite;
}

void GSprite::SetDepth(float aDepth)
{
	myDepth = aDepth;
}

void GSprite::SetAnimationIndex(int aIndex)
{
	myAnimationIndex = aIndex;
}

void GSprite::SetAnimationSpeed(float aSpeed)
{
	myAnimationSpeed = aSpeed;
}