#ifndef CAMERA_H
#define CAMERA_H
#include "SFML\Graphics.hpp"
#include <random>
#include "Math.h"

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
	int GetViewWidth() const;
	int GetViewHeight() const;
	float GetMouseX() const;
	float GetMouseY() const;
	float GetZoom() const;
	float GetMonitorWidth() const;
	float GetMonitorHeight() const;
	float GetInitialWidth() const;
	float GetInitialHeight() const;

	//Modifiers
	void SetX(float aX);
	void SetY(float aY);
	void SetZoom(float aZoom);
	void IncrZoom(float aX);
	void ShakeScreen(float aX);

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