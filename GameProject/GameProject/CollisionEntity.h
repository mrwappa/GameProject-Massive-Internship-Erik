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
	
	bool LineIntersection(Vector2f aP1, Vector2f aP2, Vector2f aP3, Vector2f aP4);
	bool CheckBoxEdges(CollisionEntity* t, CollisionEntity* o);

	CollisionEntity* ObjCollision(float aX, float aY, std::string aType);
	bool InstanceCollision(float aX, float aY, CollisionEntity* aObject);

	void UpdateBBoxManually(float aX, float aY);
	void UpdateBBox();
	void DrawBBox();

	//Compare if two rectangles contain one or the other
	bool ContainRekt(RektF aRect1, RektF aRect2);
	
	Vector2f GetBoxPosition() const;
	Vector2f Rotate(float aX, float aY, float aAngle, Vector2f Point);
	Vector2f RotatePoint(float cx, float cy, float angle, Vector2f p);
	RektF GetBounds() const;

protected:
	float myMovementSpeed;
	float myXSpeed;
	float myYSpeed;
	RektF myBoundingBox;

	float myBoxXOffset;
	float myBoxYOffset;
	float myBoxWidth;
	float myBoxHeight;
};

#endif // !COLLISION_ENTITY