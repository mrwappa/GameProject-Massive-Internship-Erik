#ifndef WALL_H
#define WALL_H

#include "Solid.h"

#define WALLL "Sprites/Blocks/spr_wallL.png"
#define WALLDL "Sprites/Blocks/spr_wallLD.png"
#define WALLM "Sprites/Blocks/spr_wallM.png"
#define WALLMD "Sprites/Blocks/spr_wallMD.png"
#define WALLMM "Sprites/Blocks/spr_wallMM.png"
#define WALLR "Sprites/Blocks/spr_wallR.png"
#define WALLRD "Sprites/Blocks/spr_wallRD.png"

class Wall : public Solid
{
public:
	Wall(float aX, float aY);
	~Wall();

	void Update();
	void Draw();

};
#endif // !WALL_H