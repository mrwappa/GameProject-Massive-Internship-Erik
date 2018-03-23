#pragma once //because the PCH warning wants to suck some big belony
#ifndef QUADTREE_H
#define QUADTREE_H

#include "QuadNode.h"

template <typename T>
class QuadTree
{
public:

	QuadTree(RektF aRectangle, int aMaxLevels, int aSplitSize);
	~QuadTree();
	
	int Count() const;
	void Insert(T* aObject);
	GrowingArray<T*>* FindIntersecting(RektF aArea);
	GrowingArray<T*>* Find(RektF aArea);

private:
	QuadNode<T*>* myRootNode;
};

template<typename T>
inline QuadTree<T>::QuadTree(RektF aRectangle, int aMaxLevels, int aSplitSize)
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
inline void QuadTree<T>::Insert(T* aObject)
{
	myRootNode->Insert(aObject);
}

template<typename T>
inline GrowingArray<T*>* QuadTree<T>::FindIntersecting(RektF aArea)
{
	return myRootNode->FindIntersecting(aArea,GrowingArray<T>());
}

template<typename T>
inline GrowingArray<T*>* QuadTree<T>::Find(RektF aArea)
{
	return myRootNode->Find(aArea, GrowingArray<T>());
}

#endif // !QUADTREE_H*/