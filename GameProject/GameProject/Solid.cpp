#include "stdafx.h"
#include "Solid.h"

void Solid::OnRemoval()
{
	RemoveCollInstance("Solid", this);
}

Solid::Solid()
{
	AddCollInstance("Solid", this);
}


Solid::~Solid()
{
}
