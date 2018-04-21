#pragma once
#include <Box2D\Box2d.h>
class Entity
{
protected:
	std::unique_ptr<b2Body> Body;
public:
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

