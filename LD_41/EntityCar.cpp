#include "EntityCar.h"
#include "World.h"
#include <iostream>


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
	BodyDef.position.Set(1, 1); //set the starting position
	BodyDef.angle = 0; //set the starting angle
	BodyDef.linearDamping = 0.5;
	BodyDef.angularDamping = 0.8;
	Body = world->CreateBody(&BodyDef);
	Shape.SetAsBox(3.744, 1.5);
	FixtureDef.shape = &Shape;
	FixtureDef.density = 1;
	FixtureDef.restitution = 0.2;
	Body->CreateFixture(&FixtureDef);
}
void EntityCar::UpdatePhysics() {
	Entity::UpdatePhysics();	
	static constexpr float Drag = 1;
	float32 angle = Body->GetAngle();
	b2Vec2 vel = Body->GetLinearVelocity();
	b2Vec2 velNorm = vel;
	float DotProduct = 0;
	//Sideways skid restitution
	//float32 force = velNorm.Length();
	//velNorm.Normalize();
	/*float SkidDrag = 0.5;
	float DotProduct = -((-sin(angle) * vel.x) + (cos(angle) * vel.y)) * SkidDrag;
	Body->ApplyLinearImpulseToCenter(b2Vec2(-sin(angle) * Drag * DotProduct, cos(angle) * Drag  * DotProduct), true);*/
	//Wheel drag
	//Front
	float Speed = vel.Length();
	float WheelDrag = 0.2;
	constexpr float MaxSpeed = 50;
	//if (Speed > 0) {
	//	//3000 == max speed
	//	std::cout <<"S"<< Speed << "\n";
	//	Speed = std::min(MaxSpeed - 1, Speed);
	//	WheelDrag /= std::min((MaxSpeed/(MaxSpeed - Speed)),5.0f);
	//	std::cout << WheelDrag << "\n";
	//}
	float32 WheelAngle = angle + SteerAngle;
	DotProduct = -((-sin(WheelAngle) * vel.x) + (cos(WheelAngle) * vel.y)) * WheelDrag;
	Body->ApplyLinearImpulse(b2Vec2(-sin(WheelAngle) * DotProduct, cos(WheelAngle) * DotProduct), Body->GetWorldPoint(b2Vec2(2, 0)), true);
	//Back
	WheelAngle = angle;
	DotProduct = -((-sin(WheelAngle) * vel.x) + (cos(WheelAngle) * vel.y)) *0.9;
	Body->ApplyLinearImpulse(b2Vec2(-sin(WheelAngle) * DotProduct * WheelDrag, cos(WheelAngle) * DotProduct * WheelDrag), Body->GetWorldPoint(b2Vec2(-3, 0)), true);

	DriveForce = std::max(std::min(DriveForce, MaxDriveForce), -MaxDriveForce);
	Body->ApplyForce(b2Vec2(cos(angle) * DriveForce, sin(angle) * DriveForce), Body->GetWorldPoint(b2Vec2(-3, 0)), true);
	////
	float RotationalDrag = 0.5;
	float32 RelVel = -Body->GetAngularVelocity();
	Body->ApplyAngularImpulse(RelVel * RotationalDrag, true);
}