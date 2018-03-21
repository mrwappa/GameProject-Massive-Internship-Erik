#pragma once //because the PCH warning wants to suck some big belony
#ifndef QUADTREE_H
#define QUADTREE_H

#define ARRAY_SAFE_DELETE(a) if(a!= NULL) delete[] a; a = NULL;
#define SAFE_DELETE(a) if(a != NULL) delete(a); a = NULL;

#include "QuadNode.h"
#include "Rectangle.h"

template <typename T>
class QuadTree
{
public:

	QuadTree(Rectangle<float> aRectangle, int aMaxLevels, int aSplitSize);
	~QuadTree();
	
	int Count() const;
	void Insert(T aObject);
	GrowingArray<T>* FindIntersecting(Rectangle<float> aArea);
	GrowingArray<T>* Find(Rectangle<float> aArea);

private:
	QuadNode<T>* myRootNode;

};

template<typename T>
inline QuadTree<T>::QuadTree(Rectangle<float> aRectangle, int aMaxLevels, int aSplitSize)
{
	myRootNode = new QuadNode<T>(aRectangle, aMaxLevels, aSplitSize);
}

template<typename T>
inline QuadTree<T>::~QuadTree()
{

}

template<typename T>
inline int QuadTree<T>::Count() const
{
	return myRootNode->Count();
}

template<typename T>
inline void QuadTree<T>::Insert(T aObject)
{
	myRootNode->Insert(aObject);
}

template<typename T>
inline GrowingArray<T>* QuadTree<T>::FindIntersecting(Rectangle<float> aArea)
{
	return myRootNode->FindInterSecting(aArea,GrowingArray<T>());
}

template<typename T>
inline GrowingArray<T>* QuadTree<T>::Find(Rectangle<float> aArea)
{
	return myRootNode->Find(aArea, GrowingArray<T>());
}

#endif // !QUADTREE_H