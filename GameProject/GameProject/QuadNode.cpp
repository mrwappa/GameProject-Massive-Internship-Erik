#include "stdafx.h"
#include "QuadNode.h"

template<typename T>
QuadNode<T>::QuadNode(RektF aBounds, int aLevelsLeft, int aSplitSize)
{
	myBounds = aBounds;
	myLevelsLeft = aLevelsLeft;
	mySplitSize = aSplitSize;
	myHasSplit = myLevelsLeft <= 0;
}

template<typename T>
inline QuadNode<T>::~QuadNode()
{

}

template<typename T>
void QuadNode<T>::CreateChildNodes()
{
	//should this be after the levelsleft check?
	myHasSplit = true;
	if (myLevelsLeft <= 0) { return; }
	
	float halfWidth = myBounds.GetWidth() / 2.0f;
	float halfHeight = myBounds.GetHeight() / 2.0f;

	//there will be memory leaks ATM
	myChildNodes[0] = (new QuadNode<T*>(RektF(myBounds.GetX(), myBounds.GetY(), halfWidth, halfHeight), myLevelsLeft - 1, mySplitSize));
	myChildNodes[1] = (new QuadNode<T*>(RektF(myBounds.GetX(), myBounds.GetY() + halfHeight, halfWidth, halfHeight), myLevelsLeft - 1, mySplitSize));
	myChildNodes[2] = (new QuadNode<T*>(RektF(myBounds.GetX() + halfWidth, myBounds.GetY(), halfWidth, halfHeight), myLevelsLeft - 1, mySplitSize));
	myChildNodes[3] = (new QuadNode<T*>(RektF(myBounds.GetX() + halfWidth, myBounds.GetY() + halfHeight, halfWidth, halfHeight), myLevelsLeft - 1, mySplitSize));
}

template<typename T>
bool QuadNode<T>::IsEmpty() const
{
	return myBounds.IsEmpty() or (myObjects.Size() == 0 and myChildNodes[0] == NULL and myChildNodes[1] == NULL and myChildNodes[2] == NULL and myChildNodes[3] == NULL);
}

template<typename T>
int QuadNode<T>::Count() const
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		if (myChildNodes[i] != NULL)
		{
			count += myChildNodes[i]->Count();
		}
	}
	count += myObjects.Size();
	return count;
}

template<typename T>
RektF QuadNode<T>::GetBounds() const
{
	return myBounds;
}

template<typename T>
void QuadNode<T>::AddSubTreeContent(GrowingArray<T*>* aResult)
{
	for (int i = 0; i < 4; i++)
	{
		if (myChildNodes[i] != NULL)
		{
			myChildNodes[i]->AddSubTreeContent(aResult);
		}
	}
	aResult->AddRange(myObjects);
}

template<typename T>
GrowingArray<T*> QuadNode<T>::Find(RektF aQueryArea, GrowingArray<T*>* aResult)
{
	aResult->AddRange(myObjects);
	for (int i = 0; i < 4; i++)
	{
		if (myChildNodes[i] != NULL)
		{
			if (myChildNodes[i]->IsEmpty()) { continue; }

			if (myChildNodes[i]->GetBounds().Contains(aQueryArea))
			{
				myChildNodes[i]->Find(aQueryArea, aResult);
				break;
			}
			if (aQueryArea.Contains(myChildNodes[i]->GetBounds()))
			{
				myChildNodes[i]->AddSubTreeContent(aResult);
				continue;
			}
			if (myChildNodes[i]->GetBounds().Intersect(aQueryArea))
			{
				myChildNodes[i]->Find(aQueryArea, aResult);
			}

		}
	}

	return aResult;
}

template<typename T>
GrowingArray<T*> QuadNode<T>::FindIntersecting(RektF aQueryArea, GrowingArray<T*>* aResult)
{
	for (int i = 0; i < myObjects.Size(); i++)
	{
		//could be a problem here with the fact that T is template class and GetBounds is specific method
		if (aQueryArea.Intersect(myObjects[i]->GetBounds()))
		{
			aResult->Add(myObjects[i]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (myChildNodes[i] != NULL)
		{
			if (myChildNodes[i]->IsEmpty()) { continue; }

			//Case 1
			if (myChildNodes[i]->GetBounds().Contains(aQueryArea))
			{
				myChildNodes[i]->FindIntersecting(aQueryArea, aResult);
				break;
			}

			//Case 2
			if (aQueryArea.Contains(myChildNodes[i]->GetBounds()))
			{
				myChildNodes[i]->AddSubTreeContent(aResult);
				continue;
			}

			//Case 3
			if (myChildNodes[i]->GetBounds().Intersect(aQueryArea))
			{
				myChildNodes[i]->FindInterSecting(aQueryArea, aResult);
			}
		}
	}
	
	return aResult;
}

template<typename T>
void QuadNode<T>::Insert(T* aObject)
{
	if (!myBounds.Contains(aObject->GetBounds())) { return; }

	if (!myHasSplit)
	{
		if (myObjects.Size() < mySplitSize)
		{
			myObjects.Add(aObject);
			return;
		}
		else
		{
			CreateChildNodes();

			GrowingArray<T*> tmpArray = myObjects;
			myObjects.RemoveAll();

			for (int i = 0; i < tmpArray.Size(); i++)
			{
				Insert(tmpArray[i]);
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (myChildNodes[i] != NULL)
		{
			if (myChildNodes[i]->GetBounds().Contains(aObject->GetBounds()))
			{
				myChildNodes[i]->Insert(aObject);
				return;
			}
		}
	}

	myObjects.Add(aObject);
}

template<typename T>
bool QuadNode<T>::HasChildNodes()
{
	return myChildNodes[0] != NULL and myChildNodes[1] != NULL and myChildNodes[2] != NULL and myChildNodes[3] != NULL;
}

template<typename T>
bool QuadNode<T>::DeleteChildNodes()
{
	if (HasChildNodes()) 
	{
		for (int i = 0; i < 4; i++)
		{
			delete myChildNodes[i];
		}
		return true;
	}
	return false;
}

template<typename T>
void QuadNode<T>::DeleteChildNodesRecursive()
{
	if (DeleteChildNodes())
	{
		for (int i = 0; i < 4; i++)
		{
			myChildNodes[i]->DeleteChildNodesRecursive();
		}
	}
}
