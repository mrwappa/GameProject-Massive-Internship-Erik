#include "stdafx.h"
#include "GSprite.h"

sf::RenderWindow* GSprite::Window;
sf::Shader* GSprite::DepthShader;
GrowingArray<GSprite*> GSprite::SpriteList;
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

	myWidth = myTextureWidth * aXScale / myNrOfFrames;
	myHeight = myTextureHeight * aYScale;
	int diameter = myWidth > myHeight ? myWidth : myHeight;

	if (aX + diameter / 2 > Camera->GetX() - Camera->GetViewWidth() / 2 and aX - diameter / 2 < Camera->GetX() + Camera->GetViewWidth() / 2 and
		aY + diameter / 2 > Camera->GetY() -Camera->GetViewHeight() / 2 and aY - diameter / 2 < Camera->GetY() + Camera->GetViewHeight() / 2)
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

		myDepth = -aDepth;
		SpriteList.Add(this);
	}
	
}

GSprite* GSprite::Partition(int aLow, int aHigh)
{
	GSprite* pivot = SpriteList[aHigh];
	int i = aLow -1;

	for (int j = aLow; j <= aHigh-1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (SpriteList[j]->GetDepth() <= pivot->GetDepth())
		{
			i++;
			SpriteList.Swap(i, j);
		}
	}
	SpriteList.Swap(i + 1, aHigh);
	return SpriteList[i + 1];
}

void GSprite::QuickSort(int aLow, int aHigh)
{
	if (aLow < aHigh)
	{
		GSprite* partition = Partition(aLow, aHigh);
		int partitionIndex = SpriteList.Find(partition);
		if (partitionIndex > 0)
		{
			QuickSort(aLow, partitionIndex -1);
			QuickSort(partitionIndex + 1, aHigh);
		}
	}
}

void GSprite::SortDepth()
{
	std::cout << SpriteList.Size() << "\n";
	if(SpriteList.Size() > 1)
	{
		QuickSort(0, SpriteList.Size()-1);
	}
}

void GSprite::DrawAllSprites()
{
	SortDepth();
	//draw sprites
	for (int i = 0; i < SpriteList.Size(); i++)
	{
		Window->draw(SpriteList[i]->GetSprite());
	}
	//remove sprites
	SpriteList.RemoveAll();
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