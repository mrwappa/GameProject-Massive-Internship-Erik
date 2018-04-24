#include "stdafx.h"
#include "Entity.h"

std::map<std::string, GrowingArray<Entity*>*> Entity::SuperList;
GrowingArray<Entity*>* Entity::GrArrayPtr;
GrowingArray<Entity*> Entity::DeleteMarkedList;
GrowingArray<Entity*> Entity::DrawList;
GrowingArray<Entity*> Entity::NonDrawList;
InputHandler* Entity::Input;
Camera* Entity::Camera;
GSprite Entity::Pixel;
sf::Font* Entity::MainFont;
std::thread* Entity::SortDrawThread;
bool Entity::SortInDrawThread = true;
bool Entity::DrawListSorted = false;
bool Entity::DrawListUnfinished = false;
Entity::Entity()
{
	
}


Entity::~Entity()
{

}

void Entity::Init(std::string aName, float aX, float aY)
{
	SortInDrawThread = false;
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
	myDrawing = true;
	myOutOfLoop = false;
	myMarkedForDelete = false;
	AddInstance(this,aName);
	DrawList.Add(this);
	myInDrawList = false;
	SortInDrawThread = true;
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
	SortInDrawThread = false;

	if (DeleteMarkedList.Size() > 0)
	{
		for (int i = 0; i < DeleteMarkedList.Size(); i++)
		{
			DeleteInstanceMem(DeleteMarkedList[i]);
		}

		DeleteMarkedList.RemoveAll();
	}

	SortInDrawThread = true;
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

GSprite * Entity::GetSprite()
{
	return &mySprite;
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

void Entity::SetActive(const bool aBool)
{
	myActive = aBool;
}

void Entity::SetDrawing(const bool aBool)
{
	myDrawing = aBool;
}

void Entity::SetInDrawList(bool aBool)
{
	myInDrawList = aBool;
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

void Entity::SortDrawList()
{
	while (true)
	{
		if (SortInDrawThread)
		{
			BubbleSortInDrawThread();	
		}
	}
	
	/*while (true)
	{
		if (SortInDrawThread)
		{
			QuickSort(0, DrawList.Size() - 1);
		}
	}*/
}

void Entity::BubbleSort()
{
	
	bool swapped;
	SortInDrawThread = false;
	for (int i = 0; i < DrawList.Size(); i++)
	{
		swapped = false;
		for (int j = 0; j < DrawList.Size() - i - 1; j++)
		{
			if (DrawList[j]->GetDepth() > DrawList[j + 1]->GetDepth())
			{
				DrawList.Swap(j, j + 1);
				swapped = true;
			}
		}
		if (swapped == false)
		{
			break; 
		}
		
	}

	SortInDrawThread = true;
}

void Entity::BubbleSortInDrawThread()
{
	bool swapped;

	for (int i = 0; i < DrawList.Size(); i++)
	{
		swapped = false;
		for (int j = 0; j < DrawList.Size() - i - 1; j++)
		{
			if (!SortInDrawThread) { return; }
			if (DrawList[j]->GetDepth() > DrawList[j + 1]->GetDepth())
			{
				DrawList.Swap(j, j + 1);
				DrawListSorted = false;
				swapped = true;
			}
		}
		if (swapped == false) { DrawListUnfinished = false; break; }

	}
	DrawListSorted = true;
	
}

void Entity::DrawAll()
{
	
	/*if (DrawList.Size() > 1)
	{
		QuickSort(0, DrawList.Size() - 1);
	}*/

	
	//SetDrawList();
	SortInDrawThread = false;
	for (int i = 0; i < DrawList.Size(); i++)
	{
		if (DrawList[i]->GetDrawing())
		{
			DrawList[i]->Draw();
		}
	}
	SortInDrawThread = true;
	
}

void Entity::SetDrawList()
{
	
	/*GrowingArray<std::pair<Entity*,int>> nonChangeList;
	GrowingArray<std::pair<Entity*,int>> drawChangeList;

	int cameraWidth = Camera->GetViewWidth();
	int cameraHeight = Camera->GetViewHeight();
	int cameraX = Camera->GetX();
	int cameraY = Camera->GetY();
	
	for (int i = 0; i < NonDrawList.Size(); i++)
	{
		Entity* instance = NonDrawList[i];

		//this is an extremely crude way of saying that some entities get drawn, but not others
		float x = instance->GetX();
		float y = instance->GetY();
		float width = abs(instance->GetWidth()) * 3;
		float height = abs(instance->GetHeight()) * 3;
		float diameter = width >= height ? width : height;

		if ((x - (diameter / 2)) < cameraX + (cameraWidth / 2) and (x + (diameter / 2)) > cameraX - (cameraWidth / 2) and
			(y - (diameter / 2)) < cameraY + (cameraHeight / 2) and (y + (diameter / 2)) > cameraY - (cameraHeight / 2))
		{
			nonChangeList.Add(std::pair<Entity*, int>(instance, i));
		}
	}

	for (int i = 0; i < nonChangeList.Size(); i++)
	{
		DrawList.Add(nonChangeList[i].first);
		NonDrawList.RemoveCyclicAtIndex(nonChangeList[i].second);
	}


	for (int i = 0; i < DrawList.Size(); i++)
	{
		Entity* instance = DrawList[i];
		
		float x = instance->GetX();
		float y = instance->GetY();
		float width = abs(instance->GetWidth()) * 3;
		float height = abs(instance->GetHeight()) * 3;
		float diameter = width >= height ? width : height;

		if (!((x - (diameter / 2)) < cameraX + (cameraWidth / 2) and (x + (diameter / 2)) > cameraX - (cameraWidth / 2) and
			(y - (diameter / 2)) < cameraY + (cameraHeight / 2) and (y + (diameter / 2)) > cameraY - (cameraHeight / 2)))
		{
			nonChangeList.Add(std::pair<Entity*, int>(instance, i));
		}
	}

	for (int i = 0; i < drawChangeList.Size(); i++)
	{
		NonDrawList.Add(drawChangeList[i].first);
		DrawList.RemoveCyclicAtIndex(drawChangeList[i].second);
	}*/
	SortInDrawThread = false;
	int cameraWidth = Camera->GetViewWidth();
	int cameraHeight = Camera->GetViewHeight();
	int cameraX = Camera->GetX();
	int cameraY = Camera->GetY();

	for (auto const &instance : Entity::SuperList)
	{
		for (int i = 0; i < instance.second->Size(); i++)
		{
			Entity* anInstance = instance.second->FindAtIndex(i);

			float x = anInstance->GetX();
			float y = anInstance->GetY();
			float width = abs(anInstance->GetWidth()) * 3;
			float height = abs(anInstance->GetHeight()) * 3;
			float diameter = width >= height ? width : height;

			if (!anInstance->GetInDrawList())
			{
				if ((x - (diameter)) < cameraX + (cameraWidth / 2) and (x + (diameter)) > cameraX - (cameraWidth / 2) and
					(y - (diameter)) < cameraY + (cameraHeight / 2) and (y + (diameter)) > cameraY - (cameraHeight / 2))
				{
					DrawList.Add(anInstance);
					NonDrawList.Remove(anInstance);
					anInstance->SetInDrawList(true);
				}
			}
			else
			{
				if (!((x - (diameter / 2)) < cameraX + (cameraWidth / 2) and (x + (diameter / 2)) > cameraX - (cameraWidth / 2) and
					(y - (diameter / 2)) < cameraY + (cameraHeight / 2) and (y + (diameter / 2)) > cameraY - (cameraHeight / 2)))
				{
					DrawList.Remove(anInstance);
					NonDrawList.Add(anInstance);
					anInstance->SetInDrawList(false);
				}
			}
		}
	}

	SortInDrawThread = true;
}

void Entity::DrawRect(float aX, float aY, float aWidth, float aHeight, float aAngle, float aAlpha, sf::Color aColor)
{
	Pixel.Draw(aX, aY, aWidth, aHeight, aAngle, aAlpha, aColor,0);
}

void Entity::DrawRectGUI(float aX, float aY, float aWidth, float aHeight, float aAngle, float aAlpha, sf::Color aColor)
{
	Pixel.Draw(aX + Camera->GetX() - Camera->GetViewWidth() / 2, aY + Camera->GetY() - Camera->GetViewHeight() / 2, aWidth, aHeight, aAngle, aAlpha, aColor, 0);
}

void Entity::DrawLinePos(float aX1, float aY1, float aX2, float aY2, sf::Color aColor)
{

	float deltax = aX2 - aX1;
	float deltay = aY2 - aY1;

	float deltalength = Math::SQRT2((deltax * deltax) + (deltay * deltay));

	Pixel.DrawOrigin(aX1, aY1, 0, 0, 1, deltalength, Math::RadToDeg(atan2f(deltay, deltax)) - 90, 1, aColor, 0);
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

	float posX = Camera->GetX() + (aX / Camera->GetZoom() - Camera->GetViewWidth() / 2);
	float posY = Camera->GetY() + (aY / Camera->GetZoom() - Camera->GetViewHeight() / 2);
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

bool Entity::GetDrawing() const
{
	return myDrawing;
}

bool Entity::GetOutOfLoop() const
{
	return myOutOfLoop;
}

bool Entity::GetInDrawList() const
{
	return myInDrawList;
}
