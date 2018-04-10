#ifndef GROUNDPILLAR_H
#define GROUNDPILLAR_H

#include "Entity.h"

#define PILLARL "Sprites/Blocks/spr_pillarL.png"
#define PILLARR "Sprites/Blocks/spr_pillarR.png"
#define PILLARM "Sprites/Blocks/spr_pillarM.png"

class GroundPillar : public Entity
{
public:
	GroundPillar(float aX ,float aY, int aPillar);
	~GroundPillar();

	enum PillarType{ Left, Middle, Right};
};

#endif // !GROUNDPILLAR_H