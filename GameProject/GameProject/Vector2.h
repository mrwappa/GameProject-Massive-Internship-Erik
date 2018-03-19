#ifndef VECTOR2_H
#define VECTOR2_H

#define SQRT_MAGIC_F 0x5f3759df 
#include <math.h>

template<class TType>
class Vector2
{
public:
	Vector2();
	Vector2(TType aX, TType aY);
	~Vector2();

	Vector2 operator*(const Vector2 &aVector);
	Vector2 operator/(const Vector2 &aVector);
	Vector2 operator+(const Vector2 &aVector);
	Vector2 operator-(const Vector2 &aVector);

	Vector2 &operator*=(const Vector2 &aVector);
	Vector2 &operator/=(const Vector2 &aVector);
	Vector2 &operator+=(const Vector2 &aVector);
	Vector2 &operator-=(const Vector2 &aVector);

	Vector2 operator*(TType aType);
	Vector2 operator/(TType aType);
	Vector2 operator+(TType aType);
	Vector2 operator-(TType aType);

	Vector2 &operator*=(TType aType);
	Vector2 &operator/=(TType aType);
	Vector2 &operator+=(TType aType);
	Vector2 &operator-=(TType aType);

	Vector2 &operator=(const Vector2 &aVector);

	TType Length();
	TType FullLength();

	//Vector2 SetRotate(double aRad);
	Vector2 Rotate(double aRad);

	TType Dot(const Vector2 &aVector);

	TType SQRT2(const float aX);

	Vector2 Normalize();

	union
	{
		TType myX;
		TType x;
		TType myU;
		TType u;
	};

	union
	{
		TType myY;
		TType y;
		TType myV;
		TType v;
	};
};


//CONSTRUCTOR
template<class TType>
inline Vector2<TType>::Vector2()
{
	myX = 0;
	myY = 0;
}

//DEFINE VECTOR CONSTRUCTOR
template<class TType>
inline Vector2<TType>::Vector2(TType aX, TType aY)
{
	myX = aX;
	myY = aY;

}

//DESTRUCTOR 
template<class TType>
inline Vector2<TType>::~Vector2()
{
	myX = 0;
	myY = 0;
}

//MULTIPLY
template<class TType>
inline Vector2<TType> Vector2<TType>::operator*(const Vector2 &aVector)
{
	return Vector2(myX * aVector.myX, myY * aVector.myY);
}

//DIVIDE
template<class TType>
inline Vector2<TType> Vector2<TType>::operator/(const Vector2 &aVector)
{
	return Vector2(myX / aVector.myX, myY / aVector.myY);
}

//ADDITION
template<class TType>
inline Vector2<TType> Vector2<TType>::operator+(const Vector2 &aVector)
{
	return Vector2(myX + aVector.myX, myY + aVector.myY);
}

//SUBTRACTION
template<class TType>
inline Vector2<TType> Vector2<TType>::operator-(const Vector2 &aVector)
{
	return Vector2(myX - aVector.myX, myY - aVector.myY);
}

//MULTIPLY ITSELF
template<class TType>
inline Vector2<TType>& Vector2<TType>::operator*=(const Vector2 &aVector)
{
	myX *= aVector.myX;
	myY *= aVector.myY;
	return *this;
}

//DIVIDE ITSELF
template<class TType>
inline Vector2<TType>& Vector2<TType>::operator/=(const Vector2 &aVector)
{
	myX /= aVector.myX;
	myY /= aVector.myY;
	return *this;
}

//ADD  ITSELF
template<class TType>
inline Vector2<TType>& Vector2<TType>::operator+=(const Vector2 &aVector)
{
	myX += aVector.myX;
	myY += aVector.myY;
	return *this;
}

//SUBTRACT ITSELF
template<class TType>
inline Vector2<TType>& Vector2<TType>::operator-=(const Vector2 &aVector)
{
	myX -= aVector.myX;
	myY -= aVector.myY;
	return *this;
}

//MULTIPLY SCALAR
template<class TType>
inline Vector2<TType> Vector2<TType>::operator*(TType aType)
{
	return Vector2(myX * aType, myY * aType);
}

//DIVIDE SCALAR
template<class TType>
inline Vector2<TType> Vector2<TType>::operator/(TType aType)
{
	return Vector2(myX / aType, myY / aType);
}

//ADDITION SCALAR
template<class TType>
inline Vector2<TType> Vector2<TType>::operator+(TType aType)
{
	return Vector2(myX + aType, myY + aType);
}

//SUBTRACT SCALAR
template<class TType>
inline Vector2<TType> Vector2<TType>::operator-(TType aType)
{
	return Vector2(myX - aType, myY - aType);
}

//MULTIPLY ITSELF SCALAR
template<class TType>
inline Vector2<TType>& Vector2<TType>::operator*=(TType aType)
{
	myX *= aType;
	myY *= aType;
	return *this;
}

//DIVIDE ITSELF SCALAR
template<class TType>
inline Vector2<TType>& Vector2<TType>::operator/=(TType aType)
{
	myX *= aType;
	myY *= aType;
	return *this;
}

//ADD ITSELF SCALAR
template<class TType>
inline Vector2<TType>& Vector2<TType>::operator+=(TType aType)
{
	myX += aType;
	myY += aType;
	return *this;
}

//SUBTRACT ITSELF SCALAR
template<class TType>
inline Vector2<TType>& Vector2<TType>::operator-=(TType aType)
{
	myX -= aType;
	myY -= aType;
	return *this;
}

//EQUALS
template<class TType>
inline Vector2<TType>& Vector2<TType>::operator=(const Vector2 &aVector)
{
	myX = aVector.myX;
	myY = aVector.myY;
	return *this;
}

//LENGTH
template<class TType>
inline TType Vector2<TType>::Length()
{
	return SQRT2(myX*myX + myY * myY);
}

//FULL LENGTH
template<class TType>
inline TType Vector2<TType>::FullLength()
{
	return myX * myX + myY * myY;
}


//ROTATE
template<class TType>
inline Vector2<TType> Vector2<TType>::Rotate(double aRad)
{
	double Cos = sin(aRad);
	double Sin = sin(aRad);
	return(Vector2((myX * Cos) - (myY * Sin), (myY * Cos) + (myX * Sin)));
}

//DOT PRODUCT
template<class TType>
inline TType Vector2<TType>::Dot(const Vector2 & aVector)
{
	return myX * aVector.myX + myY * aVector.myY;
}

//NORMALIZE
template<class TType>
inline Vector2<TType> Vector2<TType>::Normalize()
{
	TType length = Length();
	myX /= length;
	myY /= length;
	return *this;
}

//"FAST" SQUARE ROOT
template<class TType>
inline TType Vector2<TType>::SQRT2(const float aX)
{
	const float xhalf = 0.5f*aX;

	union // get bits for floating value
	{
		float x;
		int i;
	} u;

	u.x = aX;
	u.i = SQRT_MAGIC_F - (u.i >> 1);  // gives initial guess y0

	return aX * u.x*(1.5f - xhalf * u.x*u.x); // Newton step, repeating increases accuracy 
}
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<int> Vector2i;

#endif // !VECTOR2_H