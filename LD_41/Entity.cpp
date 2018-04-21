#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::Update()
{
	UpdatePhysics();
}

void Entity::UpdatePhysics()
{

}

void Entity::UpdatePhysics()
{
	Rotation = Body->GetAngle();
	Pos = Body->GetPosition();
	Body->ApplyForceToCenter(Acc, true);
}
void Entity::SetPosition(b2Vec2 pos)
{
	Pos = pos;
	Body->SetTransform(pos, Body->GetAngle());
}