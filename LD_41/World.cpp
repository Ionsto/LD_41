#include "World.h"



World::World()
{
	PhysicalWorld = std::make_unique<b2World>(b2Vec2(0, 0));
	InitGame();
}
void World::InitGame()
{

}

World::~World()
{
}

int World::AddEntity(std::unique_ptr<Entity> newentity)
{
	//Could use a : based loop but I want the ID for more neferious purposes
	for(int id = 0;id < MaxEntityCount;++id)
	{
		if (!EntityList[id])
		{
			newentity->Id = id;
			EntityList[id] = std::move(newentity);
			if (id > HighestEntityLocation){
				HighestEntityLocation = id;
			}
			return id;
		}
	}
	return -1;
}
void World::Update()
{

}
void World::UpdatePhysics()
{
	PhysicalWorld->Step(DeltaTime, 5, 5);
	for (int i = 0; i <= HighestEntityLocation; ++i)
	{
		if (EntityList[i])
		{
			if (EntityList[i]->Alive)
			{
				EntityList[i]->UpdatePhysics();
			}
		}
	}
}
void World::UpdateEntity()
{
	for (int i = 0; i <= HighestEntityLocation; ++i)
	{
		if (EntityList[i])
		{
			if (EntityList[i]->Alive)
			{
				EntityList[i]->Update();
			}
			else
			{
				EntityList[i] = nullptr;
			}
		}
	}
}