#include "StaticElements.h"


Hospital::Hospital(b2World * world) :
	RoofThing(world, 2.5 / 2, 2.5 / 2),
	WallTop(world, 20 / 2, 0.49),
	WallBottom(world, 20/2, 0.46),
	Building(world, 3, 8)
{
	Building.SetPosition(4.7, 20/2);
	WallTop.SetPosition(10, 0.28);
	WallBottom.SetPosition(10,19.8);
	RoofThing.SetPosition(9.3, 14.1);
}


WorldWalls::WorldWalls(b2World * world,float sx,float sy) :
	Top(world, sx/2, Size),
	Bottom(world, sx/2,Size),
	Left(world, Size,sy/2),
	Right(world, Size,sy/2)
{
	Top.SetPosition(sx / 2, -Size);
	Bottom.SetPosition(sx / 2, sy + Size);
	Left.SetPosition(-Size,sy/2);
	Right.SetPosition(sx+Size,sy / 2);
}
