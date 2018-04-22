#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{

}

void Entity::Update()
{
	//Ngl I made a mistake here
	//	UpdatePhysics();
	//}
}


void Entity::UpdatePhysics()
{
	if (Body) {
		Rotation = Body->GetAngle();
		Pos = Body->GetPosition();
		Body->ApplyForceToCenter(Acc, true);
	}
}
void Entity::SetPosition(float32 x,float32 y)
{
	Pos.x = x;
	Pos.y = y;
	if (Body) {
		Body->SetTransform(b2Vec2(x,y), Body->GetAngle());
	}
}