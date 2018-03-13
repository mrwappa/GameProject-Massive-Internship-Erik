#ifndef ENTITY_H
#define ENTITY_H

#define and &&
#define or ||

#include "SFML\Graphics.hpp"
#include "GrowingArray.h"
#include "InputHandler.h"
#include "GSprite.h"
#include "Camera.h"

class Entity
{
public:
	Entity(std::string aName);
	~Entity();
	
	static std::map<std::string, GrowingArray<Entity*>*> SuperList;
	static GrowingArray<Entity*> DeleteMarkedList;
	
	static Camera* Camera;
	
	//Add, Destroy instance in game loop
	void AddInstance(Entity* aEntity, std::string aName);
	void DestroyInstance(Entity* aEntity);
	static void DeleteInstance(Entity* aEntity);
	static void DeleteMarkedInstances();
	
	//Update,Draw
	virtual void BeginUpdate();
	virtual void Update();
	virtual void EndUpdate();
	virtual void Draw();
	virtual void DrawGUI();
	
	//Keyboard, Mouse
	static InputHandler* Input;
	bool KeyboardCheck(sf::Keyboard::Key aKey);
	bool KeyboardCheckPressed(sf::Keyboard::Key aKey);
	bool KeyboardCheckRelease(sf::Keyboard::Key aKey);
	bool KeyboardCheckReleased(sf::Keyboard::Key aKey);
	bool MouseCheck(sf::Mouse::Button aButton);
	bool MouseCheckPressed(sf::Mouse::Button aButton);
	bool MouseCheckRelease(sf::Mouse::Button aButton);
	bool MouseCheckReleased(sf::Mouse::Button aButton);
	bool MouseWheelUp();
	bool MouseWheelDown();

	//Accessors
	bool GetActive() const;
	std::string GetName() const;
	
protected:
	float myX;
	float myY;

	float myDepth;
	float myAngle;
	float myXScale;
	float myYScale;
	float myAlpha;
	sf::Color myColor;
	float myAnimationSpeed;
	
	GSprite mySprite;
	//If the entity is drawn and updated
	bool myActive;
	//Exists for design purposes(like getting an instance from the SuperList)
	std::string myName;
private:

	//this, or where entities get deleted is the current problem.
	static GrowingArray<Entity*>* GrArrayPtr;
};
#endif // !ENTITY_H