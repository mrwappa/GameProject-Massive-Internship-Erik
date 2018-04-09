#ifndef BRICK_H
#define BRICK_H

#include "Solid.h"

#define BRICKBLANK "Sprites/Blocks/spr_grassBLANK.png"
#define BRICKD "Sprites/Blocks/spr_grassD.png"
#define BRICKDL "Sprites/Blocks/spr_grassDL.png"
#define BRICKFILLED "Sprites/Blocks/spr_grassFILLED.png"
#define BRICKL "Sprites/Blocks/spr_grassL.png"
#define BRICKLR "Sprites/Blocks/spr_grassLR.png"
#define BRICKU "Sprites/Blocks/spr_grassU.png"
#define BRICKUD "Sprites/Blocks/spr_grassUD.png"
#define BRICKUDL "Sprites/Blocks/spr_grassUDL.png"
#define BRICKUL "Sprites/Blocks/spr_grassUL.png"
#define BRICKDLR "Sprites/Blocks/spr_grassDLR.png"
#define BRICKULR "Sprites/Blocks/spr_grassULR.png"

class Brick : public Solid
{
public:
	Brick(float aX, float aY);
	~Brick();

	void Update();
	void Draw();


private:
	

};

#endif // !BRICK_H