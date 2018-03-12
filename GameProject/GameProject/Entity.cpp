#include "stdafx.h"
#include "Entity.h"

std::map<char*, GrowingArray<Entity*>*> Entity::SuperList;
GrowingArray<Entity*>* Entity::GrArrayPtr;
InputHandler* Entity::Input;

Entity::Entity(char* aName)
{
	myAnimationSpeed = 0;
	myDepth = 0;
	myAngle = 0;
	myXScale = 1;
	myYScale = 1;
	myAlpha = 1;
	myColor = sf::Color::White;
	myName = aName;
	AddInstance(this, aName);
}


Entity::~Entity()
{

}

void Entity::AddInstance(Entity * aEntity, char* aName)
{
	if (SuperList.count(aName) == 0)
	{
		SuperList[aName] = new GrowingArray<Entity*>;
	}
	GrArrayPtr = SuperList.at(aName);
	GrArrayPtr->Add(aEntity);
	//Should I set GrArrayPtr to null? Wouldn't that just make it null in the SuperList as well?
}

void Entity::DestroyInstance(Entity * aEntity)
{
	DeleteMarkedList.Add(aEntity);
}

void Entity::DeleteInstance(Entity * aEntity)
{
	GrArrayPtr = SuperList.at(aEntity->GetName());
	GrArrayPtr->DeleteCyclic(aEntity);
	GrArrayPtr = nullptr;
}

void Entity::DeleteMarkedInstances()
{
	for (int i = 0; i < DeleteMarkedList.Size(); i++)
	{
		Entity::DeleteInstance(DeleteMarkedList[i]);
		DeleteMarkedList.RemoveCyclic(DeleteMarkedList[i]);
	}
}

char* Entity::GetName() const
{
	return myName;
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
}

void Entity::DrawGUI()
{
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
