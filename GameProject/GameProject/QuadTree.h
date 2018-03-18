#ifndef QUADTREE_H
#define QUADTREE_H

#define ARRAY_SAFE_DELETE(a) if(a!= NULL) delete[] a; a = NULL;
#define SAFE_DELETE(a) if(a != NULL) delete(a); a = NULL;

#include "QuadNode.h"

template <typename T>
class QuadTree
{
public:

	QuadTree(int aMinSize);
	~QuadTree();

private:
	//minimum node size
	int myMinSize = 20;
	QuadNode* myRootNode;

};

template<typename T>
inline QuadTree<T>::QuadTree(int aMinSize)
{
	myMinSize = aMinSize;
}

template<typename T>
inline QuadTree<T>::~QuadTree()
{

}


#endif // !QUADTREE_H