#ifndef QUADNODE_H
#define QUADNODE_H

#include "GrowingArray.h"
#include "SFML\Graphics.hpp"
#include "Rekt.h"

template <typename T>
class QuadNode
{
public:

	QuadNode(RektF aBounds, int aLevelsLeft, int aSplitSize);
	~QuadNode();
	void CreateChildNodes();
	bool IsEmpty() const;
	int Count() const;
	RektF GetBounds() const;

	void AddSubTreeContent(GrowingArray<T*>* aResult);
	GrowingArray<T*> Find(RektF aQueryArea, GrowingArray<T*>* aResult);
	GrowingArray<T*> FindIntersecting(RektF aQueryArea, GrowingArray<T*>* aResult);
	void Insert(T* aObject);

	bool HasChildNodes();
	bool DeleteChildNodes();
	void DeleteChildNodesRecursive();
	
private:
	GrowingArray<T*> myObjects;

	QuadNode<T*>* myChildNodes[4];

	int myLevelsLeft;
	int mySplitSize;
	bool myHasSplit;

	RektF myBounds;
};

#endif // !QUADNODE_H

