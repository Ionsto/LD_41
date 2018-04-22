#include "EntityCarAI.h"
#include "World.h"
#include <iostream>


EntityCarAI::EntityCarAI(World * world,Node * defnode) : EntityCar(world)
{
	Type = EntityType::Car;
	if (!defnode)
	{
		defnode = &world->RoadNetwork.GetDefaultNode();
	}
	TargetNode = defnode;
	LastNode = defnode;
	RandOffset = b2Vec2(0, 0);
}


EntityCarAI::~EntityCarAI()
{
}

void EntityCarAI::Update() {
	EntityCar::Update();
	//Update AI
	UpdateAI();
}
void EntityCarAI::UpdateAI() {
	if (ReverseCounter++ >= ReverseMax)
	{
		ReverseCounter = 0;
		if (!Reversing)
		{
			if ((PosReverseTracker - Pos).LengthSquared() < 2) {
				Reversing = true;
				ReverseMax = 120;
				SteerAngle = -SteerAngle;
			}
			PosReverseTracker = Pos;
		}
		else
		{
			Reversing = false;
			ReverseMax = 60;
		}
	}
	if (Reversing)
	{
		DriveForce = -MaxDriveForce/3;
	}

	//
	if (TargetNode != nullptr && !Reversing) {
		float dy = (TargetNode->Y+RandOffset.y) - Pos.y;
		float dx = (TargetNode->X + RandOffset.x) - Pos.x;
		TargetAngle = atan2f(dy,dx) - Rotation;
		while (TargetAngle > 3.14)
		{
			TargetAngle -= 3.14;
		}
		while (TargetAngle < -3.14)
		{
			TargetAngle += 3.14;
		}
		if (abs(TargetAngle) > ThresholdAngle)
		{
			SteerAngle = std::copysign(ControlAngle, TargetAngle);
		}

		float DistanceSqrd = (dy*dy)+(dx*dx);
		static constexpr float CloseDistSqrd = 20 * 20;
		if (DistanceSqrd > CloseDistSqrd)
		{
			//
			DriveForce = MaxDriveForce/2;
		}
		else
		{
			IncrementTarget();
		}
	}
}
void EntityCarAI::IncrementTarget() {
	Node * tempnode;
	while ((tempnode = GetNewNode(TargetNode)) == LastNode) {
	}
	TargetNode->Target = false;
	LastNode = TargetNode;
	TargetNode = tempnode;
	std::cout << "Prev node:" << LastNode->MyId.id << "\n";
	std::cout << "Next node:" << TargetNode->MyId.id << "\n";
	TargetNode->Target = true;
	RandOffset.x = (rand() % 10) - 5;
	RandOffset.y = (rand() % 10) - 5;
}
Node * EntityCarAI::GetNewNode(Node * currentnode) {
	return &WorldRef->RoadNetwork.GetRandomNextNode(currentnode->MyId);
}