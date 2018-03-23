#ifndef REKT_H
#define REKT_H

template <typename T>
class Rekt
{
public:
	Rekt(T aX, T aY, T aWidth, T aHeight);
	Rekt();
	~Rekt();

	Rekt &operator=(const Rekt& aRekt);

	bool IsEmpty() const;
	T GetX() const;
	T GetX2() const;
	T GetY() const;
	T GetY2() const;
	T GetWidth() const;
	T GetHeight() const;

	bool Contains(Rekt<T> aRect);
	bool Intersect(Rekt<T> aRect);

private:
	float myX;
	float myX2;
	float myY;
	float myY2;
	float myWidth;
	float myHeight;
};

template<typename T>
inline Rekt<T>::Rekt(T aX, T aY, T aWidth, T aHeight)
{
	myX = aX;
	myY = aY;
	myWidth = aWidth;
	myHeight = aWidth;
	myX2 = aX + aWidth;
	myY2 = aY + aHeight;
}

template<typename T>
inline Rekt<T>::Rekt()
{
	myX = 0;
	myY = 0;
	myWidth = 0;
	myHeight = 0;
	myX2 = 0;
	myY2 = 0;
}

template<typename T>
inline Rekt<T>::~Rekt()
{
}

template<typename T>
inline Rekt<T>& Rekt<T>::operator=(const Rekt<T>& aRekt)
{
	myX = aRekt.GetX();
	myY = aRekt.GetY();
	myWidth = aRekt.GetWidth();
	myHeight = aRekt.GetHeight();
	myX2 = aRekt.GetX2();
	myY2 = aRekt.GetY2();

	return *this;
}

template<typename T>
inline bool Rekt<T>::IsEmpty() const
{
	return myWidth == 0 and myHeight == 0;
}

template<typename T>
inline T Rekt<T>::GetX() const
{
	return myX;
}

template<typename T>
inline T Rekt<T>::GetX2() const
{
	return myX2;
}

template<typename T>
inline T Rekt<T>::GetY() const
{
	return myY;
}

template<typename T>
inline T Rekt<T>::GetY2() const
{
	return myY2;
}

template<typename T>
inline T Rekt<T>::GetWidth() const
{
	return myWidth;
}

template<typename T>
inline T Rekt<T>::GetHeight() const
{
	return myHeight;
}

template<typename T>
inline bool Rekt<T>::Contains(Rekt<T> aRect)
{
	return (aRect.GetX() >= myX and aRect.GetY() >= myY and
		aRect.GetX2() <= myX2 and aRect.GetY2() <= myY2);
}

template<typename T>
inline bool Rekt<T>::Intersect(Rekt<T> aRect)
{
	return (myX + myWidth >= aRect.GetX() and myY + myHeight >= aRect.GetY() and
		myX <= aRect.GetX() + aRect.GetWidth() and myY <= aRect.GetY() + aRect.GetHeight());
}

typedef Rekt<float> RektF;
typedef Rekt<double> RektD;
typedef Rekt<int> RektI;

#endif // !RECTANGLE_H