#pragma once
#include "Entity.h"
class EntityBuilding :
	public Entity
{
public:
	EntityBuilding(World * world);
	virtual ~EntityBuilding();
	void CreateBuilding(b2World * world);
};

