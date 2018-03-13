#ifndef CAMERA_H
#define CAMERA_H
#include "SFML\Graphics.hpp"

class Camera
{
public:
	Camera(float aX, float aY, int aMonitorWidth, int aMonitorHeight);
	~Camera();

	static sf::RenderWindow* Window;

	void Update();

	//Accessors
	float GetX() const;
	float GetY() const;

	//Modifiers
	float SetX() const;
	float SetY() const;
private:
	sf::View myView;
	float myX;
	float myY;
	float myMouseX;
	float myMouseY;

	int myIdealWidth;
	int myCorrespondingWidth;
	int myIdealHeight;
	int myWidth;
	int myHeight;
	int myViewWidth;
	int myViewHeight;

	int myMonitorWidth;
	int myMonitorHeight;
	float myAspectRatio;
	float myWidthDifference;

	float myZoom;
	float myScreenShake;


};
#endif // !CAMERA_H