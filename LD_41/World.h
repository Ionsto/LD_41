#pragma once
#include <Box2D\Box2D.h>
#include <memory>
#include <array>
#include "Entity.h"
class World
{

public:
	std::unique_ptr<b2World> PhysicalWorld;
	static constexpr int MaxEntityCount = 1000;
	int HighestEntityLocation = 0;
	std::array<std::unique_ptr<Entity>, MaxEntityCount> EntityList;
	World();
	~World();
	int AddEntity(std::unique_ptr<Entity> entity);
};

