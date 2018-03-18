#include "stdafx.h"
#include "QuadNode.h"


template<typename T>
QuadNode<T>::QuadNode(sf::Rect<int> aBounds, int aLevel, QuadTree* aOwner, QuadNode* aParent)
{
	myBounds = aBounds;
	myLevel = aLevel;
	myQuadTreeOwner = aOwner;
	myParent = aParent;
}

template<typename T>
inline QuadNode<T>::~QuadNode()
{

}

template<typename T>
void QuadNode<T>::CreateChildNodes()
{

}
