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
	Entity();
	~Entity();

	void Init(std::string aName, float aX, float aY);

	static std::map<std::string, GrowingArray<Entity*>*> SuperList;
	static GrowingArray<Entity*> DeleteMarkedList;
	
	static Camera* Camera;
	
	//Add, Destroy instance in game loop
	void AddInstance(Entity* aEntity, std::string aName);
	void DeleteInstance(Entity* aEntity);
	static void DeleteMarkedInstances();
	
	Entity* GetObj(std::string aEntity);

	//Update,Draw
	virtual void BeginUpdate();
	virtual void Update();
	virtual void EndUpdate();
	virtual void Draw();
	virtual void DrawGUI();
	
	void DrawRect(float aX, float aY, float aWidth, float aHeight, float aAngle,float aDepth , float aAlpha, sf::Color aColor);
	static sf::Sprite Pixel;

	//Keyboard, Mouse
	static InputHandler* Input;
	bool KeyboardCheck(const sf::Keyboard::Key aKey);
	bool KeyboardCheckPressed(const sf::Keyboard::Key aKey);
	bool KeyboardCheckRelease(const sf::Keyboard::Key aKey);
	bool KeyboardCheckReleased(const sf::Keyboard::Key aKey);
	bool MouseCheck(const sf::Mouse::Button aButton);
	bool MouseCheckPressed(const sf::Mouse::Button aButton);
	bool MouseCheckRelease(const sf::Mouse::Button aButton);
	bool MouseCheckReleased(const sf::Mouse::Button aButton);
	bool MouseWheelUp();
	bool MouseWheelDown();

	//Accessors
	bool GetActive() const;
	std::string GetName() const;
	float GetAngle() const;
	float GetX() const;
	float GetY() const;
	
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
	GSprite myPixel;
	//If the entity is drawn and updated
	bool myActive;
	//Exists for design purposes(like getting an instance from the SuperList)
	std::string myName;

	static void DeleteInstanceMem(Entity* aEntity);
private:

	//this, or where entities get deleted is the current problem.
	static GrowingArray<Entity*>* GrArrayPtr;
};
#endif // !ENTITY_H