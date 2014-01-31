#ifndef PICKUP_H
#define PICKUP_H

#include "WPILib.h"
#include <Math.h>
#include "util/metropidcontroller.h"

class Pickup {

	public:
		Pickup( SpeedController *motor, SpeedController *angleMotor );
		~Pickup(){};
		void Actuate();
		void Intake(double wheelSpeed);
		void ArmAngle(double upMotorSpeed);
		void Disable();
		
		enum {Pushing, Pulling, Nothing} pickupState;
		
		SpeedController *motor;
		SpeedController *angleMotor;
		
		double upMotorSpeed;
};

#endif
