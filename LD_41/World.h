#pragma once
#include <Box2D\Box2D.h>
#include <memory>
#include <array>
#include "Entity.h"
/*
A world is one game instance -> controls player state as well as general world info
*/
class World
{

public:
	static constexpr float DeltaTime = 1.0 / 60.0;
	std::unique_ptr<b2World> PhysicalWorld;
	static constexpr int MaxEntityCount = 1000;
	/*
	Fun trick here, lets pretend we are a swap-list & always contiguous
	We normally arn't deleting many things (and they tend to be at the end)
	-> we normally stay << MaxEntityCount -> don't need to check all the unallocated entities
	*/
	int HighestEntityLocation = 0;
	std::array<std::unique_ptr<Entity>, MaxEntityCount> EntityList;
	World();
	~World();
	void Update();
	void UpdatePhysics();
	void UpdateEntity();
	int AddEntity(std::unique_ptr<Entity> entity);
};

