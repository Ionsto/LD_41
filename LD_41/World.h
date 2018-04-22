#pragma once
#include <Box2D\Box2D.h>
#include <memory>
#include <array>
#include "Entity.h"
#include "EntityAmbulance.h"
#include "RoadSystem.h"
#include "StaticElements.h"
/*
A world is one game instance -> controls player state as well as general world info
*/
struct PlayerInfo {
	bool HasAccident = true;
	bool CompletedMission = false;
	float Score = 0;
	int PlayerId = 0;
	EntityAmbulance::Controls Controls;
	int Timer = 0;
	//lol
	int CrashCount = 0;
	int AccidentCount = 0;
	int AccidentCountMax = 5;
	//Idk add some more things in here
};
class World
{
public:
	static constexpr int BlockCount = 5;
	static constexpr float BuildingSize = 10;
	static constexpr int BlockBuildingCount = 5;
	static constexpr float BlockSize = BuildingSize * BlockBuildingCount;
	static constexpr float RoadWidth = 40;
	static constexpr float WorldSize = RoadWidth + ((BlockCount)*(RoadWidth+BlockSize));
	RoadSystem RoadNetwork;
	PlayerInfo Player;
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
	std::unique_ptr<Hospital> EntityHospital;
	std::unique_ptr<WorldWalls> Walls;
	World();
	~World();
	void CreateBlock(float xstart,float ystart);
	void CreateRoadNodes();
	void CreateCity();
	void InitGame();
	void Update();
	void UpdatePhysics();
	void UpdateEntity();
	int AddEntity(std::unique_ptr<Entity> entity);
	void UpdatePlayer();
	EntityEvent * GetNearAccident(Entity * entity,float Threshold = 10);
	bool GetInHospital(Entity * Entity);
};

