#include "EntityCar.h"
#include "World.h"


EntityCar::EntityCar(World * world) : Entity()
{
	Type = EntityType::Ambulence;
	WorldRef = world;
	if (world) {
		CreateCarBody(world->PhysicalWorld.get());
	}
}


EntityCar::~EntityCar()
{
	WorldRef->PhysicalWorld->DestroyBody(Body);
}

void EntityCar::CreateCarBody(b2World * world)
{
	BodyDef.type = b2_dynamicBody; //this will be a dynamic body
	BodyDef.position.Set(0, 0); //set the starting position
	BodyDef.angle = 0; //set the starting angle
	BodyDef.linearDamping = 0.125;
	BodyDef.angularDamping = 0.125;
	Body = world->CreateBody(&BodyDef);
	Shape.SetAsBox(10 / 2, 1.3 / 2);
	FixtureDef.shape = &Shape;
	FixtureDef.density = 1;
	Body->CreateFixture(&FixtureDef);
}