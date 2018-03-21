#ifndef QUADNODE_H
#define QUADNODE_H

#include "GrowingArray.h"
#include "SFML\Graphics.hpp"
#include "Rectangle.h"

template <typename T>
class QuadNode
{
public:

	QuadNode(Rectangle<float> aBounds, int aLevelsLeft, int aSplitSize);
	~QuadNode();
	void CreateChildNodes();
	bool IsEmpty() const;
	int Count() const;
	Rectangle<float> GetBounds() const;

	void AddSubTreeContent(GrowingArray<T>* aResult);
	GrowingArray<T>* Find(Rectangle<float> aQueryArea, GrowingArray<T>* aResult);
	GrowingArray<T>* FindIntersecting(Rectangle<float> aQueryArea, GrowingArray<T>* aResult);
	void Insert(T aObject);

private:
	GrowingArray<T> myObjects;

	QuadNode<T>* myChildNodes[4];

	int myLevelsLeft;
	int mySplitSize;
	bool myHasSplit;

	Rectangle<float> myBounds;

	
};

#endif // !QUADNODE_H

