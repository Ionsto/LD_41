#pragma once
#include "Entity.h"
class EntityCar :
	public Entity
{
protected:
	float32 MaxDriveForce = 300;
	float32 SteerAngle = 0;
	float32 DriveForce = 0;
public:
	EntityCar(World * world = nullptr);
	virtual ~EntityCar();
	void CreateCarBody(b2World * world);
	virtual void UpdatePhysics() override;
};

