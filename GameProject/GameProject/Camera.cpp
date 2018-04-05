#include "stdafx.h"
#include "Camera.h"

sf::RenderWindow* Camera::Window;

Camera::Camera(float aX, float aY, int aMonitorWidth, int aMonitorHeight)
{
	myX = aX;
	myY = aY;

	myMonitorWidth = aMonitorWidth;
	myMonitorHeight = aMonitorHeight;

	myIdealWidth = 540;
	myCorrespondingWidth = 960;

	myAspectRatio = (float)myMonitorWidth / (float)myMonitorHeight;
	myIdealWidth = std::round(myIdealHeight*myAspectRatio);

	//Check for odd numbers
	if (myIdealWidth % 2 != 0)
	{
		myIdealWidth++;
	}
	if (myIdealHeight % 2 != 0)
	{
		myIdealHeight++;
	}

	myWidthDifference = (float)myIdealWidth / (float)myCorrespondingWidth;
	myWidth = myIdealWidth / myWidthDifference;
	myHeight = myIdealHeight / myWidthDifference;

	myZoom = 1;
	myScreenShake = 0;

	myViewWidth = myWidth / myZoom;
	myViewHeight = myHeight / myZoom;

	myView.reset(sf::FloatRect(0, 0, myMonitorWidth, myMonitorHeight));
	myView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	myView.setSize(sf::Vector2f(myWidth, myHeight));
	myMouseX = myX - myViewWidth / 2 + sf::Mouse::getPosition().x / ((float)myMonitorWidth / (float)myViewWidth);
	myMouseY = myY - myViewHeight / 2 + sf::Mouse::getPosition().y / ((float)myMonitorHeight / (float)myViewHeight);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	myViewWidth = myWidth / myZoom;
	myViewHeight = myHeight / myZoom;
	
	myMouseX = myX - myViewWidth / 2 + sf::Mouse::getPosition().x / ((float)myMonitorWidth / (float)myViewWidth);
	myMouseY = myY - myViewHeight / 2 + sf::Mouse::getPosition().y / ((float)myMonitorHeight / (float)myViewHeight);

	myScreenShake = Math::Lerp(myScreenShake, 0, 0.55f);
	
	myView.setCenter(myX + myScreenShake * Math::IRand(-2,2), myY + myScreenShake * Math::IRand(-2, 2));
	myView.setSize(sf::Vector2f(myViewWidth, myViewHeight));
	Window->setView(myView);
}

//Accessors
float Camera::GetX() const
{
	return myX;
}

float Camera::GetY() const
{
	return myY;
}

int Camera::GetViewWidth() const
{
	return myViewWidth;
}

int Camera::GetViewHeight() const
{
	return myViewHeight;
}

float Camera::GetMouseX() const
{
	return myMouseX;
}

float Camera::GetMouseY() const
{
	return myMouseY;
}

float Camera::GetZoom() const
{
	return myZoom;
}

float Camera::GetMonitorWidth() const
{
	return myMonitorWidth;
}

float Camera::GetMonitorHeight() const
{
	return myMonitorHeight;
}

float Camera::GetInitialWidth() const
{
	return myWidth;
}

float Camera::GetInitialHeight() const
{
	return myHeight;
}

//Modifiers
void Camera::SetX(float aX) 
{
	myX = aX;
}

void Camera::SetY(float aY)
{
	myY = aY;
}

void Camera::SetZoom(float aZoom)
{
	myZoom = aZoom;
}

void Camera::IncrZoom(float aX)
{
	myZoom += aX;
}

void Camera::ShakeScreen(float aX)
{
	myScreenShake += aX;
}

