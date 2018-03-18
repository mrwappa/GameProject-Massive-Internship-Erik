#ifndef QUADNODE_H
#define QUADNODE_H

#include "GrowingArray.h"
#include "SFML\Graphics.hpp"

class QuadTree;

template <typename T>
class QuadNode
{
public:

	QuadNode(sf::Rect<int> aBounds, int aLevel, QuadTree* aOwner, QuadNode* aParent);
	~QuadNode();
	void CreateChildNodes();


private:
	GrowingArray<T> myObjects;

	QuadNode* myParent;
	QuadNode* myChildNodes[4];
	QuadTree* myQuadTreeOwner;

	int myLevel;


	sf::Rect myBounds;
	float myX;
	float myY;

	
};

#endif // !QUADNODE_H

