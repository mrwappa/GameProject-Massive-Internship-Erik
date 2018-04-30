#ifndef ENTITY_H
#define ENTITY_H

#define and &&
#define or ||

#include "SFML\Graphics.hpp"
#include "GrowingArray.h"
#include "InputHandler.h"
#include "GSprite.h"
#include "Camera.h"
#include "Alarm.h"
#include <thread>

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Init(std::string aName, float aX, float aY);

	static std::map<std::string, GrowingArray<Entity*>*> SuperList;
	static GrowingArray<Entity*> DeleteMarkedList;
	static GrowingArray<Entity*> DrawList;
	static GrowingArray<Entity*> NonDrawList;

	static Camera* Camera;
	static std::thread* SortDrawThread;
	static bool SortInDrawThread;

	//Add, Destroy instance in game loop
	void AddInstance(Entity* aEntity, std::string aName);
	void DeleteInstance(Entity* aEntity);
	virtual void OnRemoval();
	static void DeleteMarkedInstances();
	


	Entity* GetObj(std::string aEntity);

	//Update,Draw
	virtual void BeginUpdate();
	virtual void Update();
	virtual void EndUpdate();
	virtual void Draw();
	virtual void DrawGUI();

	//Sorting Entities depending on their depth
	static int Partition(int aLow, int aHigh);
	static void QuickSort(int aLow, int aHigh);
	static void SortDrawList();
	static void BubbleSort();
	static void BubbleSortInDrawThread();
	static void DrawAll();

	static bool DrawListSorted;
	static bool DrawListUnfinished;
	
	void DrawRect(float aX, float aY, float aWidth, float aHeight, float aAngle , float aAlpha, sf::Color aColor);
	void DrawRectGUI(float aX, float aY, float aWidth, float aHeight, float aAngle, float aAlpha, sf::Color aColor);
	void DrawLinePos(float aX1, float aY1, float aX2, float aY, sf::Color aColor);
	void DrawLine(float aX, float aY, float aLength, float aAngle, sf::Color aColor);
	static GSprite Pixel;

	//Font
	static sf::Font* MainFont;
	void DrawFont(std::string aText ,float aX, float aY, float aSize, float aXScale, float aYScale, sf::Color aColor);
	void DrawFontGUI(std::string aText, float aX, float aY, float aSize, float aXScale, float aYScale, sf::Color aColor);

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
	bool GetDrawing() const;
	bool GetOutOfLoop() const;
	bool GetInDrawList() const;
	std::string GetName() const;
	GSprite* GetSprite();
	float GetAngle() const;
	float GetX() const;
	float GetY() const;
	float GetDepth() const;
	float GetWidth();
	float GetHeight();
	float GetMarkedForDelete() const;

	//Modifiers
	void SetX(float aX);
	void SetY(float aY);
	void SetAngle(float aAngle);
	void SetMarkedForDelete(const bool aBool);
	void SetColor(sf::Color aColor);
	void SetActive(const bool aBool);
	void SetDrawing(const bool aBool);
	void SetInDrawList(bool aBool);

protected:
	float myX;
	float myY;
	float myPreviousX;
	float myPreviousY;

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
	bool myDrawing;
	bool myOutOfLoop;
	//Exists for design and accessibility purposes(like getting an instance from the SuperList)
	std::string myName;

	static void DeleteInstanceMem(Entity* aEntity);
	bool myMarkedForDelete;
	
private:
	//should be static as well
	sf::Text myText;
	static GrowingArray<Entity*>* GrArrayPtr;
	
	bool myInDrawList;
};
#endif // !ENTITY_H