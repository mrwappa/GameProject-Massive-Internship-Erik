#ifndef Image_H
#define Image_H

#include <string>

#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Texture.hpp"

struct Vector2f;

class Image
{
public:
	Image(const char* path, int xOffset = 0, int yOffset = 0, int width = 0, int height = 0);
    ~Image();

	sf::Sprite& GetSprite();
	void SetPosition(const Vector2f& aPosition);

private:
	bool CreateSprite(const char* path, int xOffset, int yOffset, int width, int height);

	sf::Texture myTexture;
	sf::Sprite mySprite;
    
    //debug
    std::string myName;
};

#endif
