#ifndef GSPRITE_H
#define GSPRITE_H
#include "SFML\Graphics.hpp"
#include "GrowingArray.h"
#include "SFML\OpenGL.hpp"

class GSprite
{
public:
	GSprite();
	GSprite(sf::Texture aTexture, int aNrOfFrames);
	~GSprite();
	static sf::RenderWindow* Window;

	void Draw(float aX, float aY, float aXScale, float aYScale, float aAngle, float aDepth, float aAlpha, sf::Color aColor, float aAnimationSpeed);

	//Accessors
	float GetDepth();
	sf::Sprite GetSprite();
	sf::Texture GetTexture();
	float GetTextureWidth();

	//Modifiers
	void SetTexture(std::string aFileName, int aNrOfFrames);
	void SetTexture(sf::Texture aTexture, int aNrOfFrames);
	void SetSprite(sf::Sprite aSprite);
	void SetDepth(float aDepth);
	void SetAnimationIndex(int aIndex);
	void SetAnimationSpeed(float aSpeed);

private:
	sf::Texture myTexture;
	sf::Sprite mySprite;

	float myDepth;
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
