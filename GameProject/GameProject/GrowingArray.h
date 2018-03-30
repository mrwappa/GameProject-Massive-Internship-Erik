#ifndef GROWINGARRAY_H
#define GROWINGARRAY_H

#include <iostream>
#include <iterator>

#define ARRAY_SAFE_DELETE(a) if(a!= NULL) delete[] a; a = NULL;
#define SAFE_DELETE(a) if(a != NULL) delete(a); a = NULL;

template <typename TObjectType, typename TSizeType = int>
class GrowingArray
{
public:
	GrowingArray(int cap = 5);
	GrowingArray(const GrowingArray &growingArray);
	~GrowingArray();

	TObjectType &operator[](const TSizeType index);

	//retarderat?
	TObjectType &FindAtIndex(const TSizeType index);

	GrowingArray &operator = (const GrowingArray &growingArray);

	inline void Add(const TObjectType &object);
	inline void AddRange(const GrowingArray &growingArray);

	inline void RemoveCyclic(const TObjectType &object);
	inline void Remove(const TObjectType &object);
	inline void RemoveCyclicAtIndex(TSizeType index);
	inline void DeleteCyclic(const TObjectType &object);
	inline void DeleteCyclicAtIndex(TSizeType index);

	inline void Insert(TSizeType index, const TObjectType &object, bool cyclic = false);

	inline TSizeType Find(const TObjectType &object);

	inline TObjectType &GetLast();

	inline void Swap(TSizeType indexA, TSizeType indexB);

	static const TSizeType FoundNone = -1;
	inline void RemoveAll();
	inline void DeleteAll();

	const unsigned& Size()const;

	TObjectType *begin();
	TObjectType *end();
	/*inline auto begin();
	inline auto end();*/


private:

	TSizeType myCap;
	TSizeType myNrOfElements;
	TObjectType *myArray;

	inline void Expand();
};

//CONSTRUCTOR
template<typename TObjectType, typename TSizeType>
GrowingArray<TObjectType, TSizeType>::GrowingArray(int cap)
{
	myCap = cap;
	myNrOfElements = 0;
	myArray = new TObjectType[myCap];

}

//COPY CONSTRUCTOR
template<typename TObjectType, typename TSizeType>
GrowingArray<TObjectType, TSizeType>::GrowingArray(const GrowingArray &growingArray)
{
	myCap = growingArray.myCap;
	myNrOfElements = growingArray.myNrOfElements;

	myArray = new TObjectType[myCap];
	for (TSizeType i = 0; i < myNrOfElements; i++)
	{
		myArray[i] = growingArray.myArray[i];
	}
}

//DESTRUCTOR
template<typename TObjectType, typename TSizeType>
GrowingArray<TObjectType, TSizeType>::~GrowingArray()
{
	ARRAY_SAFE_DELETE(myArray);
}

//EQUALS/ASSIGNMENT OPERATOR
template<typename TObjectType, typename TSizeType>
GrowingArray<TObjectType, TSizeType>& GrowingArray<TObjectType, TSizeType>::operator = (const GrowingArray &growingArray)
{
	ARRAY_SAFE_DELETE(myArray);

	myCap = growingArray.myCap;
	myNrOfElements = growingArray.myNrOfElements;

	myArray = new TObjectType[myCap];
	for (TSizeType i = 0; i < myNrOfElements; i++)
	{
		myArray[i] = growingArray.myArray[i];
	}

	return *this;
}

//INDEX OPERATOR
template<typename TObjectType, typename TSizeType>
TObjectType& GrowingArray<TObjectType, TSizeType>::operator[](const TSizeType index)
{
	if (index < 0 || index >= myNrOfElements)
	{
		throw "OUT OF BOUNDS!";
	}

	return myArray[index];

}

//WHEN INDEX OPERATOR FAILS
template<typename TObjectType, typename TSizeType>
inline TObjectType & GrowingArray<TObjectType, TSizeType>::FindAtIndex(const TSizeType index)
{
	if (index < 0 || index >= myNrOfElements)
	{
		throw "OUT OF BOUNDS!";
	}

	return myArray[index];
}

//INSERT
template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::Insert(TSizeType index, const TObjectType &object, bool cyclic)
{
	if (index < 0 || index > myNrOfElements)
	{
		throw "OUT OF BOUNDS!";
	}
	else if (index == myNrOfElements)
	{
		Add(object);
	}
	else
	{
		//Am I checking this one too many times?
		if (myNrOfElements + 1 >= myCap)
		{
			Expand();
		}
		if (cyclic == false)
		{
			if (++myNrOfElements > myCap)
			{
				Expand();
			}
			for (TSizeType i = myNrOfElements; i > index; i--)
			{
				myArray[i] = myArray[i - 1];
			}
			myArray[index] = object;
		}
		else
		{
			if (myNrOfElements + 1 >= myCap)
			{
				Expand();
			}
			myNrOfElements++;
			myArray[myNrOfElements - 1] = myArray[index];
			myArray[index] = object;
		}
	}
}

//FIND FROM OBJECT
template<typename TObjectType, typename TSizeType>
inline TSizeType GrowingArray<TObjectType, TSizeType>::Find(const TObjectType & object)
{
	for (TSizeType i = 0; i < myNrOfElements; i++)
	{
		if (myArray[i] == object)
		{
			return i;
		}
	}

	return FoundNone;
}

//GETLAST
template<typename TObjectType, typename TSizeType>
inline TObjectType& GrowingArray<TObjectType, TSizeType>::GetLast()
{
	return myArray[myNrOfElements - 1];
}


//CYCLING DELETE AT INDEX
template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::DeleteCyclicAtIndex(TSizeType index)
{
	SAFE_DELETE(myArray[index]);
	myArray[index] = GetLast();
	myNrOfElements--;
}

//CYCLING DELETE FROM OBJECT
template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::DeleteCyclic(const TObjectType &object)
{
	DeleteCyclicAtIndex(Find(object));
}

//CYCLING REMOVE FROM OBJECT
template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::RemoveCyclic(const TObjectType &object)
{
	RemoveCyclicAtIndex(Find(object));
}

template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::Remove(const TObjectType & object)
{
	int index = Find(object);
	for (int i = index; i < myNrOfElements-1; i++)
	{
		myArray[i] = myArray[i+1]
	}
	myNrOfElements--;
}

//CYCLING REMOVE AT INDEX
template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::RemoveCyclicAtIndex(TSizeType index)
{
	myArray[index] = GetLast();
	myNrOfElements--;
}

//DELETE ALL
template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::DeleteAll()
{
	for (TSizeType i = 0; i < myNrOfElements; i++)
	{
		SAFE_DELETE(myArray[i]);
	}
	myNrOfElements = 0;
}

//REMOVE ALL
template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::RemoveAll()
{
	myNrOfElements = 0;
}

//EXPAND/RESIZE
template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::Expand()
{
	myCap *= 2;

	TObjectType *temp = new TObjectType[myCap];

	for (TSizeType i = 0; i < myNrOfElements; i++)
	{
		temp[i] = myArray[i];
	}
	ARRAY_SAFE_DELETE(myArray);

	myArray = temp;
	//ARRAY_SAFE_DELETE(temp);
}

//ADD
template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::Add(const TObjectType &object)
{
	if (myNrOfElements >= myCap)
	{
		Expand();
	}
	myArray[myNrOfElements++] = object;
}

template<typename TObjectType, typename TSizeType>
inline void GrowingArray<TObjectType, TSizeType>::AddRange(const GrowingArray & growingArray)
{

	for (TSizeType i = 0; i < growingArray.Size(); i++)
	{
		if (myNrOfElements >= myCap) { Expand(); }
		myArray[myNrOfElements++] = growingArray[i];
	}
}

//SIZE OF GROWINGARRAY
template<typename TObjectType, typename TSizeType>
const unsigned& GrowingArray<TObjectType, TSizeType>::Size()const
{
	return myNrOfElements;
}

template<typename TObjectType, typename TSizeType>
inline TObjectType * GrowingArray<TObjectType, TSizeType>::begin()
{
	return &myArray[0];
}

template<typename TObjectType, typename TSizeType>
inline TObjectType * GrowingArray<TObjectType, TSizeType>::end()
{
	return &myArray[myNrOfElements - 1];
}

//SWAP ELEMENTS
template<typename TObjectType, typename TSizeType>
void GrowingArray<TObjectType, TSizeType>::Swap(TSizeType indexA, TSizeType indexB)
{
	TObjectType tempObject = myArray[indexA];
	myArray[indexA] = myArray[indexB];
	myArray[indexB] = tempObject;
}

#endif // !GROWINGARRAY_H