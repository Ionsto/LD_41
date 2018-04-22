#pragma once
#include "EntityCar.h"
#include "RoadSystem.h"
class EntityCarAI :
	public EntityCar
{
protected:
	float TargetAngle = 0;
	Node * TargetNode = nullptr;
	Node * LastNode = nullptr;
	static constexpr float ControlAngle = (30 / 180.0)*3.14;
	static constexpr float ThresholdAngle = (5.0 / 180.0)*3.14;
	b2Vec2 PosReverseTracker;
	b2Vec2 RandOffset;
	int ReverseCounter = 0;
	int ReverseMax = 60;
	bool Reversing = false;
public:
	EntityCarAI(World * world = nullptr,Node * defnode = nullptr);
	virtual ~EntityCarAI();
	virtual void Update() override;
	void UpdateAI();
	Node * GetNewNode(Node * currentnode);
	void IncrementTarget();
};

