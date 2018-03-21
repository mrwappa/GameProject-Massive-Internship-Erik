#ifndef RECTANGLE_H
#define RECTANGLE_H

template <typename T>
class Rectangle
{
public:
	Rectangle(T aX, T aY, T aWidth, T aHeight);
	Rectangle();
	~Rectangle();

	bool IsEmpty() const;
	T GetX() const;
	T GetX2() const;
	T GetY() const;
	T GetY2() const;
	T GetWidth() const;
	T GetHeight() const;

	bool Contains(Rectangle<T> aRect);
	bool Intersect(Rectangle<T> aRect);

private:
	float myX;
	float myX2;
	float myY;
	float myY2;
	float myWidth;
	float myHeight;
};

template<typename T>
inline Rectangle<T>::Rectangle(T aX, T aY, T aWidth, T aHeight)
{
	myX = aX;
	myY = aY;
	myWidth = aWidth;
	myHeight = aWidth;
	myX2 = aX + aWidth;
	myY2 = aY + aHeight;
}

template<typename T>
inline Rectangle<T>::Rectangle()
{
	myX = 0;
	myY = 0;
	myWidth = 0;
	myHeight = 0;
	myX2 = 0;
	myY2 = 0;
}

template<typename T>
inline Rectangle<T>::~Rectangle()
{
}

template<typename T>
inline bool Rectangle<T>::IsEmpty() const
{
	return myWidth == 0 and myHeight == 0;
}

template<typename T>
inline T Rectangle<T>::GetX() const
{
	return myX;
}

template<typename T>
inline T Rectangle<T>::GetX2() const
{
	return myX2;
}

template<typename T>
inline T Rectangle<T>::GetY() const
{
	return myY;
}

template<typename T>
inline T Rectangle<T>::GetY2() const
{
	return myY2;
}

template<typename T>
inline T Rectangle<T>::GetWidth() const
{
	return myWidth;
}

template<typename T>
inline T Rectangle<T>::GetHeight() const
{
	return myHeight;
}

template<typename T>
inline bool Rectangle<T>::Contains(Rectangle<T> aRect)
{
	return aRect.GetX() >= myX and aRect.GetY() >= myY and
		   aRect.GetX2() <= myX2 and aRect.GetY2() <= myY2;
}

template<typename T>
inline bool Rectangle<T>::Intersect(Rectangle<T> aRect)
{
	return myX + myWidth >= aRect.GetX() and myY + myHeight >= aRect.GetY() and
		   myX <= aRect.GetX() + aRect.GetWidth() and myY <= aRect.GetY() + aRect.GetHeight();
}



#endif // !RECTANGLE_H	

