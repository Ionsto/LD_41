#include "EntityBuilding.h"
#include "World.h"



EntityBuilding::EntityBuilding(World * world) : Entity()
{
	Type = EntityType::Building;
	WorldRef = world;
	if (world) {
		CreateBuilding(world->PhysicalWorld.get());
	}
}


EntityBuilding::~EntityBuilding()
{
	WorldRef->PhysicalWorld->DestroyBody(Body);
}

void EntityBuilding::CreateBuilding(b2World * world)
{
	BodyDef.type = b2_staticBody; //this will be a dynamic body
	BodyDef.position.Set(0, 0); //set the starting position
	BodyDef.angle = 0; //set the starting angle
	Body = world->CreateBody(&BodyDef);
	Shape.SetAsBox(5, 5);
	FixtureDef.shape = &Shape;
	FixtureDef.density = 1;
	Body->CreateFixture(&FixtureDef);
}