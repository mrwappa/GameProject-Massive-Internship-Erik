#ifndef GSPRITE_H
#define GSPRITE_H
#include "SFML\Graphics.hpp"
#include "GrowingArray.h"
#include "SFML\OpenGL.hpp"
#include "Camera.h"

#define and &&
#define or ||

class GSprite
{
public:
	GSprite();
	~GSprite();
	static sf::RenderWindow* Window;
	static std::map<std::string, std::pair<sf::Texture*,sf::Sprite*>*> SpriteList;
	static Camera* Camera;
	
 	static void DeleteAllSprites();

	//A GSprite can only be drawn in the game world or GUI, not both at once
	void Draw(float aX, float aY, float aXScale, float aYScale, float aAngle, float aAlpha, sf::Color aColor, float aAnimationSpeed);
	void DrawOrigin(float aX, float aY, float aOriginX, float aOriginY, float aXScale, float aYScale, float aAngle, float aAlpha, sf::Color aColor, float aAnimationSpeed);
	void DrawGUI(float aX, float aY, float aXScale, float aYScale, float aAngle, float aAlpha, sf::Color aColor, float aAnimationSpeed);

	//Accessors
	float GetTextureWidth();
	float GetTextureHeight();
	int GetAnimationIndex() const;
	int GetNrOfFrames() const;
	int GetAnimationCounter() const;

	//Modifiers
	void SetTexture(std::string aFileName, int aNrOfFrames);
	void SetAnimationIndex(int aIndex);
	void SetAnimationSpeed(float aSpeed);

private:
	sf::Texture* myTexture;
	sf::Sprite* mySprite;
	
	float myWidth;
	float myHeight;
	float myTextureWidth;
	float myTextureHeight;

	float myNrOfFrames;
	float myAnimationIndex;
	float myAnimationSpeed;
	float myAnimationCounter;
};
#endif // !GSPRITE_H
