#pragma once
#include "Entity.h"
class EntityEvent :
	public Entity
{
public:
	int Timer = 0;
	int MaxTimer = 60*50;//50 seconds
	EntityEvent();
	virtual ~EntityEvent();
	virtual void UpdatePhysics() override;
	virtual void Update() override;
};

