#include "World.h"



World::World()
{
	PhysicalWorld = std::make_unique<b2World>(b2Vec2(0, 0));
}


World::~World()
{
}

int World::AddEntity(std::unique_ptr<Entity> newentity)
{
	for (auto & entity : EntityList)
	{
		if (!entity)
		{
			entity = std::move(newentity);
		}
	}
}