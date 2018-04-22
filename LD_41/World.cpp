#include "World.h"
#include "EntityCar.h"
#include "EntityCarAI.h"
#include "EntityAmbulance.h"
#include "EntityBuilding.h"
#include <iostream>

World::World()
{
	PhysicalWorld = std::make_unique<b2World>(b2Vec2(0, 0));
	InitGame();
}
void World::InitGame(){
	int id = AddEntity(std::make_unique<EntityAmbulance>(this));
	EntityList[id]->SetPosition(10, 10);
	CreateCity();
	//Tutorial one
	id = AddEntity(std::make_unique<EntityEvent>());
	EntityList[id]->SetPosition(50, 10);
	for (auto & node : RoadNetwork.NodeMap)	{
		id = AddEntity(std::make_unique<EntityCarAI>(this,&node));
		EntityList[id]->SetPosition(node.X, node.Y);
		static_cast<EntityCarAI*>(EntityList[id].get())->IncrementTarget();
	}
}
void World::CreateBlock(float xstart,float ystart) {
	for (int x = 0; x < World::BlockBuildingCount; ++x) {
		for (int y = 0; y < World::BlockBuildingCount; ++y) {
			if (x % (World::BlockBuildingCount-1) == 0 || y % (World::BlockBuildingCount - 1) == 0)
			{
				int id = AddEntity(std::make_unique<EntityBuilding>(this));
				EntityList[id]->SetPosition(x*BuildingSize + xstart + (BuildingSize/2), y*BuildingSize + ystart + (BuildingSize/2));
			}
		}
	}
}

void World::CreateCity() {
	for (int x = 0; x < World::BlockCount; ++x) {
		for (int y = 0; y < World::BlockCount; ++y) {
			float xp = (x * (World::BlockSize + World::RoadWidth)) + (World::RoadWidth);
			float yp = (y * (World::BlockSize + World::RoadWidth)) + (World::RoadWidth);
			CreateBlock(xp, yp);
		}
	}
	CreateRoadNodes();
	EntityHospital = std::make_unique<Hospital>(PhysicalWorld.get());
	Walls = std::make_unique<WorldWalls>(PhysicalWorld.get(),WorldSize,WorldSize);
}
void World::CreateRoadNodes() {
	//Start at the root node
	constexpr int Stride = World::BlockCount + 1;
	for (int x = 0; x < Stride; ++x) {
		for (int y = 0; y < Stride; ++y) {
			float posx = (x * (RoadWidth + BlockSize)) + RoadWidth / 2;
			float posy = (y * (RoadWidth + BlockSize)) + RoadWidth / 2;
			NodeId id = NodeId(0);
			if (x != 0 || y != 0) {
				Node newNode(posx, posy);
				id = RoadNetwork.AddNode(std::move(newNode));
			}
			auto & enode = RoadNetwork.GetNode(id);
			if (x != 0)
			{
				enode.AddConnection(id.id - Stride, 1);
			}
			if (x != World::BlockCount)
			{
				enode.AddConnection(id.id + Stride, 1);
			}
			if (y != 0)
			{
				enode.AddConnection(id.id - 1, 1);
			}
			if (y != World::BlockCount)
			{
				enode.AddConnection(id.id + 1, 1);
			}
		}
	}
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
			if (id >= HighestEntityLocation){
				HighestEntityLocation = id+1;
			}
			return id;
		}
	}
	return -1;
}
void World::Update()
{
	UpdatePlayer();
	UpdatePhysics();
	UpdateEntity();
}
void World::UpdatePhysics()
{
	PhysicalWorld->Step(DeltaTime, 5, 5);
	for (int i = 0; i < HighestEntityLocation; ++i)
	{
		if (EntityList[i])
		{
			if (EntityList[i]->Alive)
			{
				EntityList[i]->UpdatePhysics();
				EntityList[i]->UpdatePhysics();
			}
		}
	}
}
void World::UpdateEntity()
{
	for (int i = 0; i < HighestEntityLocation; ++i)
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
void World::UpdatePlayer()
{
	if (EntityList[Player.PlayerId])
	{
		Player.Timer++;
		EntityAmbulance * playerentity = static_cast<EntityAmbulance*>(EntityList[Player.PlayerId].get());
		playerentity->Inputs = Player.Controls;
		if (Player.CompletedMission)
		{
			//Tell the player, good job!
			std::cout << "fire mission\n";
			Player.HasAccident = false;
			Player.CompletedMission = false;
		}
		if (!Player.HasAccident)
		{
			//Create an accident?!?!!
			int xid = 0;
			int yid = 0;
			while (xid == 0 && yid == 0){
				xid = std::round(rand() % (World::BlockCount + 1));
				yid = std::round(rand() % (World::BlockCount + 1));
			}
			float posx = xid * (RoadWidth + BlockSize) + RoadWidth / 2;
			float posy = yid * (RoadWidth + BlockSize) + RoadWidth / 2;
			int id = AddEntity(std::make_unique<EntityEvent>());
			EntityList[id]->SetPosition(posx, posy);
			Player.HasAccident = true;
			if (Player.AccidentCount++ == Player.AccidentCountMax)
			{
				//Stop the game!
			}
		}
	}
}
EntityEvent * World::GetNearAccident(Entity * entity,float Threshold) {
	for (int i = 0; i < HighestEntityLocation; ++i)
	{
		if (EntityList[i] && entity != EntityList[i].get())
		{
			if (EntityList[i]->Alive)
			{
				if (EntityList[i]->Type == Entity::EntityType::Accident)
				{
					b2Vec2 diff = EntityList[i].get()->Pos - entity->Pos;
					if (diff.Length() < Threshold) {
						return static_cast<EntityEvent*>(EntityList[i].get());
					}
				}
			}
		}
	}
	return nullptr;
}
bool World::GetInHospital(Entity * entity) {
	return entity->Pos.x < RoadWidth / 2 && entity->Pos.y < RoadWidth / 2;
}