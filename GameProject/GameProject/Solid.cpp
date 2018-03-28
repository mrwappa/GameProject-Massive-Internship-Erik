#include "stdafx.h"
#include "Solid.h"


Solid::Solid()
{
	AddCollInstance("Solid", this);
}


Solid::~Solid()
{
}

void Solid::OnRemoval()
{
	RemoveCollInstance("Solid", this);
	CollisionEntity::OnRemoval();
}