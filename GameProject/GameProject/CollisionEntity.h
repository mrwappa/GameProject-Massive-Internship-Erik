#ifndef COLLISION_ENTITY
#define COLLISION_ENTITY

#include "Entity.h"
#include "Vector2.h"
#include "QuadTree.h"
#include "Math.h"
#include "AStar.h"

class CollisionEntity : public Entity
{
public:
	CollisionEntity();
	~CollisionEntity();
	
	void Init(std::string aName, float aX, float aY);
	static std::map<std::string, GrowingArray<CollisionEntity*>*> CollisionList;

	void OnRemoval();

	static AStar* AStarGrid;
	bool InsideGrid(float aX, float aY);
	static Vector2f SnapToGrid(float aX, float aY);
	static float SnapToGrid(float aX);
	static Vector2f GridSnapMouse();

	bool LineIntersection(Vector2f aP1, Vector2f aP2, Vector2f aP3, Vector2f aP4);
	bool LineToEdgeIntersection(Vector2f aStart, Vector2f aEnd, CollisionEntity* aObject);
	bool CheckBoxEdges(CollisionEntity* t, CollisionEntity* o);

	CollisionEntity* ObjCollision(float aX, float aY, std::string aName);
	GrowingArray<CollisionEntity*> ObjCollisionList(float aX, float aY, std::string aName);
	GrowingArray<CollisionEntity*> ObjDistanceList(float aX, float aY, float aDistance, std::string aName);
	bool InstanceCollision(float aX, float aY, CollisionEntity* aObject, bool aUpdateBBox = true);
	void PreventCollision(std::string aName);
	CollisionEntity* LineEdgeCollision(Vector2f aStart, Vector2f aEnd, std::string aName);
	CollisionEntity* NearestInstance(float aX, float aY, std::string aName);
	bool ObjPosition(float aX, float aY, std::string aName);

	void UpdateBBoxManually(float aX, float aY);
	void UpdateBBox();
	void DrawBBox();

	void Draw();
	
	//Rotate() is broken, so is the Rotate() in the Vector2 class
	Vector2f Rotate(float aX, float aY, float aAngle, Vector2f Point);
	Vector2f RotatePoint(float aX, float aY, float aAngle, Vector2f Point);

	void Move(float aXSpeed, float aYSpeed);

	//Compare if two rectangles contain one or the other
	bool ContainRekt(RektF aRect1, RektF aRect2);

	//Accessors
	Vector2f GetBoxPosition() const;
	RektF GetBounds() const;
	float GetZ() const;
	float GetXOffset();
	float GetYOffset();
	float GetXSpeed() const;
	float GetYSpeed() const;
	float GetXKnock() const;
	float GetYKnock() const;
	float GetDamage() const;

	//Modifiers
	void SetXOffset(float aX);
	void SetYOffset(float aY);
	void IncrHP(float aX);
	void SetXKnock(float aX);
	void SetYKnock(float aY);
	void SetDirection(float aDirection);

protected:
	
	float myZ;

	float myMoveSpeed;
	float myDirection;
	float myXSpeed;
	float myYSpeed;
	float myXKnockBack;
	float myYKnockBack;

	RektF myBoundingBox;

	float myBoxXOffset;
	float myBoxYOffset;
	float myBoxWidth;
	float myBoxHeight;

	float myHP;
	float myDamage;
	
	void AddCollInstance(CollisionEntity* aEntity);
	void AddCollInstance(std::string aName, CollisionEntity* aEntity);
	void RemoveCollInstance(CollisionEntity* aEntity);
	void RemoveCollInstance(std::string aName, CollisionEntity* aEntity);

private:
	
	static GrowingArray<CollisionEntity*>* GrArrayPtr;
};

#endif // !COLLISION_ENTITY