#pragma once
#include <Box2D\Box2d.h>
/*
Entity format similar to another project I did with box2d (insofar as they are both top down)

*/
class World;
class Entity
{
protected:
	b2PolygonShape Shape;
	b2FixtureDef FixtureDef;
	b2BodyDef BodyDef;
	b2Body * Body = nullptr;
	World * WorldRef = nullptr;
public:
	//Fastest reflection system you can do :/
	enum EntityType {
		Other,
		Person,
		Accident,
		Car,
		Ambulence
	}Type;
	//Probably should use a class ID -> no weird issues
	int Id = -1;
	bool Alive = true;
	b2Vec2 Pos;
	b2Vec2 Acc;
	float32 Rotation;
	Entity();
	virtual ~Entity();
	virtual void UpdatePhysics();
	virtual void Update();
	void SetPosition(b2Vec2 pos);
};

