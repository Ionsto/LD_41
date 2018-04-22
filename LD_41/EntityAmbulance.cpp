#include "EntityAmbulance.h"
#include "World.h"
#include <iostream>


EntityAmbulance::EntityAmbulance(World * world) : EntityCar(world){
	MaxDriveForce = ControlPowerMax;
}

EntityAmbulance::~EntityAmbulance(){

}

void EntityAmbulance::Update(){
	EntityCar::Update();
	UpdateInputs();
}

void EntityAmbulance::UpdateInputs(){
	if (Inputs.PickUp) {
		std::cout << "Fire pickup"<<std::endl;
		float Speed = Body->GetLinearVelocity().Length();
		if (Speed < MaxPickUpSpeed) {
			if (!HasPassenger)
			{
					EntityEvent * event = WorldRef->GetNearAccident(this,20);
					if (event)
					{
						event->Alive = false;
						std::cout << "Got person\n";
						HasPassenger = true;
					}
			}
			else
			{
				if (WorldRef->GetInHospital(this))
				{
					HasPassenger = false;
					WorldRef->Player.CompletedMission = true;
					std::cout << "Brought back person\n";
				}
			}
		}
	}
	bool Exclusion = Inputs.Left && Inputs.Right;
	Inputs.Left = Inputs.Left && !Exclusion;
	Inputs.Right = Inputs.Right && !Exclusion;
	Exclusion = Inputs.Forward && Inputs.Backward;
	Inputs.Forward = Inputs.Forward && !Exclusion;
	Inputs.Backward = Inputs.Backward && !Exclusion;
	SteerAngle = 0;
	if (Inputs.Left) {
		SteerAngle = -ControlAngle;
	}
	if (Inputs.Right) {
		SteerAngle = ControlAngle;
	}
	float ApplyForce = 0;
	if (Inputs.Forward) {
		ApplyForce = ControlPowerMax;
		//ControlPower += ControlChangeUp;
	}
	if (Inputs.Backward) {
		ApplyForce = -ControlPowerMax *0.5;
		//ControlPower -= ControlChangeDown;
	}
	DriveForce = ApplyForce;
}