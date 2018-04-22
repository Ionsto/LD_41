#pragma once
#include <Box2D\Box2d.h>
class StaticBody {
	b2BodyDef BodyDef;
	b2PolygonShape Shape;
	b2FixtureDef FixtureDef;
	b2Body * Body;
	b2World * WorldRef;
public:
	StaticBody(b2World * world,float sx,float sy){
		WorldRef = world;
		BodyDef.type = b2_staticBody; //this will be a dynamic body
		BodyDef.position.Set(0, 0); //set the starting position
		BodyDef.angle = 0; //set the starting angle
		Body = world->CreateBody(&BodyDef);
		Shape.SetAsBox(sx, sy);
		FixtureDef.shape = &Shape;
		Body->CreateFixture(&FixtureDef);
	}
	~StaticBody() {
		WorldRef->DestroyBody(Body);
	}
	void SetPosition(float x, float y) {
		Body->SetTransform(b2Vec2(x, y),0);
	}
};

class Hospital
{
protected:
	StaticBody Building;
	StaticBody RoofThing;
	StaticBody WallTop;
	StaticBody WallBottom;
public:
	Hospital(b2World * world);
};


class WorldWalls
{
protected:
	StaticBody Top;
	StaticBody Bottom;
	StaticBody Left;
	StaticBody Right;
public:
	static constexpr float Size = 1;
	WorldWalls(b2World * world,float sx,float sy);
};

