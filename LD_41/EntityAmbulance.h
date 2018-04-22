#pragma once
#include "EntityCar.h"
#include "EntityEvent.h"
class EntityAmbulance :
	public EntityCar
{
protected:
	float ControlPower = 0;
	float ControlPowerMax = 600;
	float ControlDecay = 1;
	float ControlChangeUp = 5;
	float ControlChangeDown = 5;
	static constexpr float ControlAngle = (30.0 / 180.0)*3.14;
	static constexpr float MaxPickUpSpeed = 10;
public:
	struct Controls
	{
		bool Left = false;
		bool Right = false;
		bool Forward = false;
		bool Backward = false;
		bool PickUp = false;
	}Inputs;
	bool HasPassenger = false;
	EntityAmbulance(World * world = nullptr);
	virtual ~EntityAmbulance();
	virtual void Update();
	void UpdateInputs();
};

