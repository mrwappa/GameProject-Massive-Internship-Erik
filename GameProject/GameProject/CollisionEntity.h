#ifndef COLLISION_ENTITY
#define COLLISION_ENTITY

#include "Entity.h"
#include "Vector2.h"
#include "QuadTree.h"
#include "Math.h"

class CollisionEntity : public Entity
{
public:
	CollisionEntity();
	~CollisionEntity();
	
	void Init(std::string aName, float aX, float aY);
	static std::map<std::string, GrowingArray<CollisionEntity*>*> CollisionList;

	void OnRemoval();

	bool LineIntersection(Vector2f aP1, Vector2f aP2, Vector2f aP3, Vector2f aP4);
	bool CheckBoxEdges(CollisionEntity* t, CollisionEntity* o);

	CollisionEntity* ObjCollision(float aX, float aY, std::string aName);
	bool InstanceCollision(float aX, float aY, CollisionEntity* aObject, bool aUpdateBBox = true);
	void PreventCollision(std::string aName);

	void UpdateBBoxManually(float aX, float aY);
	void UpdateBBox();
	void DrawBBox();
	
	void Move(float aXSpeed, float aYSpeed);

	//Compare if two rectangles contain one or the other
	bool ContainRekt(RektF aRect1, RektF aRect2);
	
	//Accessors
	Vector2f GetBoxPosition() const;
	//Rotate() is broken, so is the Rotate() in the Vector2 class
	Vector2f Rotate(float aX, float aY, float aAngle, Vector2f Point);
	Vector2f RotatePoint(float aX, float aY, float aAngle, Vector2f Point);
	RektF GetBounds() const;
	float GetXOffset();
	float GetYOffset();

	//Modifiers
	void SetXOffset(float aX);
	void SetYOffset(float aY);

protected:

	float myMovementSpeed;
	float myXSpeed;
	float myYSpeed;
	float myXKnockBack;
	float myYKnockBack;

	RektF myBoundingBox;

	float myBoxXOffset;
	float myBoxYOffset;
	float myBoxWidth;
	float myBoxHeight;

	void AddCollInstance(CollisionEntity* aEntity);
	void AddCollInstance(std::string aName, CollisionEntity* aEntity);
	void RemoveCollInstance(CollisionEntity* aEntity);
	void RemoveCollInstance(std::string aName, CollisionEntity* aEntity);

private:

	
	static GrowingArray<CollisionEntity*>* GrArrayPtr;
};

#endif // !COLLISION_ENTITY