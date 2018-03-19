#ifndef COLLISION_ENTITY
#define COLLISION_ENTITY

#include "Entity.h"
#include "Vector2.h"

class CollisionEntity : public Entity
{
public:
	CollisionEntity();
	~CollisionEntity();


	bool LineIntersection(Vector2<float> aP1, Vector2<float> aP2, Vector2<float> aP3, Vector2<float> aP4);
	bool CheckBoxEdges(CollisionEntity* t, CollisionEntity* o);

	/*
		When making the actual collision-checking , make sure to do 
		normal intersection checking if the angles are 0,90,180,270,360.
		Also before the check, make sure to: GetAngle() % 360, to get a
		number from 0-360.
	*/

	Vector2<float> GetBoxPosition() const;
	sf::Rect<float> GetBoundingBox() const;

protected:
	float myMovementSpeed;
	float myXSpeed;
	float myYSpeed;
	sf::Rect<float> myBoundingBox;
};

#endif // !COLLISION_ENTITY