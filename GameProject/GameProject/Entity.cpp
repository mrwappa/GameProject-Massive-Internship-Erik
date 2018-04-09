#include "stdafx.h"
#include "Entity.h"

std::map<std::string, GrowingArray<Entity*>*> Entity::SuperList;
GrowingArray<Entity*>* Entity::GrArrayPtr;
GrowingArray<Entity*> Entity::DeleteMarkedList;
GrowingArray<Entity*> Entity::DrawList;
InputHandler* Entity::Input;
Camera* Entity::Camera;
GSprite Entity::Pixel;
sf::Font* Entity::MainFont;

Entity::Entity()
{
	
}


Entity::~Entity()
{

}

void Entity::Init(std::string aName, float aX, float aY)
{
	myX = aX;
	myY = aY;
	myPreviousX = aX;
	myPreviousY = aY;
	myAnimationSpeed = 0;
	myDepth = 0;
	myAngle = 0;
	myXScale = 1;
	myYScale = 1;
	myAlpha = 1;
	myColor = sf::Color::White;
	myName = aName;
	myActive = true;
	myMarkedForDelete = false;
	AddInstance(this,aName);
	DrawList.Add(this);
}

void Entity::AddInstance(Entity* aEntity, std::string aName)
{
	if (SuperList.count(aName) == 0)
	{
		SuperList[aName] = new GrowingArray<Entity*>;
	}
	GrArrayPtr = SuperList.at(aName);
	GrArrayPtr->Add(aEntity);
}

void Entity::DeleteInstance(Entity* aEntity)
{
	//This bool check is here so that two of the same instances do not get
	//put in the same list, leading to it trying delete something empty
	if (!aEntity->GetMarkedForDelete())
	{
		aEntity->SetMarkedForDelete(true);
		DeleteMarkedList.Add(aEntity);
	}
}

void Entity::OnRemoval()
{
	
}

void Entity::DeleteInstanceMem(Entity* aEntity)
{
	DrawList.Remove(aEntity);
	aEntity->OnRemoval();
	GrArrayPtr = SuperList.at(aEntity->GetName());
	GrArrayPtr->DeleteCyclic(aEntity);
}

void Entity::DeleteMarkedInstances()
{
	if (DeleteMarkedList.Size() > 0)
	{
		for (int i = 0; i < DeleteMarkedList.Size(); i++)
		{
			DeleteInstanceMem(DeleteMarkedList[i]);
		}

		DeleteMarkedList.RemoveAll();
	}
}

Entity * Entity::GetObj(std::string aEntity)
{
	GrArrayPtr = SuperList.at(aEntity);
	if (GrArrayPtr->Size() > 0)
	{
		return GrArrayPtr->FindAtIndex(0);
	}
	return NULL;
}

std::string Entity::GetName() const
{
	return myName;
}

float Entity::GetAngle() const
{
	return myAngle;
}

float Entity::GetX() const
{
	return myX;
}

float Entity::GetY() const
{
	return myY;
}

float Entity::GetDepth() const
{
	return myDepth;
}

float Entity::GetWidth()
{
	return mySprite.GetTextureWidth() * myXScale;
}

float Entity::GetHeight()
{
	return mySprite.GetTextureHeight() * myYScale;
}

float Entity::GetMarkedForDelete() const
{
	return myMarkedForDelete;
}

void Entity::SetX(float aX)
{
	myX = aX;
}

void Entity::SetY(float aY)
{
	myY = aY;
}

void Entity::SetAngle(float aAngle)
{
	myAngle = aAngle;
}

void Entity::SetMarkedForDelete(const bool aBool)
{
	myMarkedForDelete = aBool;
}

void Entity::SetColor(sf::Color aColor)
{
	myColor = aColor;
}

void Entity::BeginUpdate()
{
}

void Entity::Update()
{
}

void Entity::EndUpdate()
{
}

void Entity::Draw()
{
	if (mySprite.GetTextureWidth() > 0)
	{
		mySprite.Draw(myX, myY, myXScale, myYScale, myAngle, myAlpha, myColor, myAnimationSpeed);
	}
}

void Entity::DrawGUI()
{

}

int Entity::Partition(int aLow, int aHigh)
{
	int i = aLow;
	int j = aHigh + 1;
	while (true)
	{
		while (DrawList[++i]->GetDepth() < DrawList[aLow]->GetDepth())
		{
			if (i == aHigh)
			{
				break;
			}
		}
		while (DrawList[aLow]->GetDepth() < DrawList[--j]->GetDepth())
		{
			if (j == aLow)
			{
				break;
			}
		}

		if (i >= j) break;

		DrawList.Swap(i, j);
	}

	DrawList.Swap(aLow, j);

	return j;
}

void Entity::QuickSort(int aLow, int aHigh)
{
	if (aHigh <= aLow) return;

	int j = Partition(aLow, aHigh);
	QuickSort(aLow, j - 1);
	QuickSort(j + 1, aHigh);
}

void Entity::DrawAll()
{
	if (DrawList.Size() > 1)
	{
		QuickSort(0, DrawList.Size() - 1);
	}
	for (int i = 0; i < DrawList.Size(); i++)
	{
		DrawList[i]->Draw();
	}
}

void Entity::DrawRect(float aX, float aY, float aWidth, float aHeight, float aAngle, float aDepth, float aAlpha, sf::Color aColor)
{
	Pixel.Draw(aX, aY, aWidth, aHeight, aAngle, aAlpha, aColor,0);
}

void Entity::DrawFont(std::string aText, float aX, float aY, float aSize, float aXScale ,float aYScale, sf::Color aColor)
{
	if (myText.getFont() == NULL) 
	{
		myText.setFont(*MainFont);
		
	}
	const_cast<sf::Texture&>(MainFont->getTexture(aSize)).setSmooth(false);
	myText.setString(aText);
	myText.setCharacterSize(aSize);
	myText.setFillColor(aColor);
	myText.setPosition(aX, aY);
	myText.setScale(aXScale, aYScale);
	
	Camera->Window->draw(myText);
}

void Entity::DrawFontGUI(std::string aText, float aX, float aY, float aSize, float aXScale, float aYScale, sf::Color aColor)
{
	if (myText.getFont() == NULL)
	{
		myText.setFont(*MainFont);

	}


	const_cast<sf::Texture&>(MainFont->getTexture(aSize)).setSmooth(false);
	myText.setString(aText);
	myText.setCharacterSize(aSize);
	myText.setFillColor(aColor);

	float posX = Camera->GetX() + round(aX / Camera->GetZoom() - Camera->GetViewWidth() / 2);
	float posY = Camera->GetY() + round(aY / Camera->GetZoom() - Camera->GetViewHeight() / 2);
	myText.setPosition(posX, posY);

	myText.setScale(aXScale / Camera->GetZoom(), aYScale / Camera->GetZoom());
	myText.setStyle(sf::Text::Regular);
	
	Camera->Window->draw(myText);
}

bool Entity::KeyboardCheck(sf::Keyboard::Key aKey)
{
	return Input->keyData[aKey] > 0;
}

bool Entity::KeyboardCheckPressed(sf::Keyboard::Key aKey)
{
	return Input->keyData[aKey] == 2;
}

bool Entity::KeyboardCheckRelease(sf::Keyboard::Key aKey)
{
	return Input->keyData[aKey] == -1;
}

bool Entity::KeyboardCheckReleased(sf::Keyboard::Key aKey)
{
	return Input->keyData[aKey] == 0;
}

bool Entity::MouseCheck(sf::Mouse::Button aButton)
{
	return Input->mouseData[aButton] > 0;
}

bool Entity::MouseCheckPressed(sf::Mouse::Button aButton)
{
	return Input->mouseData[aButton] == 2;
}

bool Entity::MouseCheckRelease(sf::Mouse::Button aButton)
{
	return Input->mouseData[aButton] == -1;
}

bool Entity::MouseCheckReleased(sf::Mouse::Button aButton)
{
	return Input->mouseData[aButton] == 0;
}

bool Entity::MouseWheelUp()
{
	return Input->MouseWheelUp;
}

bool Entity::MouseWheelDown()
{
	return Input->MouseWheelDown;
}

bool Entity::GetActive() const
{
	return myActive;
}
