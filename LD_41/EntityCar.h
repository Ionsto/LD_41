#pragma once
#include "Entity.h"
class EntityCar :
	public Entity
{
protected:
	float32 DriveForce = 100;
	float32 SteerAngle = 0;
	float32 SteerForce = 10;
public:
	EntityCar();
	virtual ~EntityCar();
};

