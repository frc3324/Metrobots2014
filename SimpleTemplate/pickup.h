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
		void RunIntake(double wheelSpeed);
		void ArmAngle(double upMotorSpeed);
		void Raise();
		void Lower();
		void Intake();
		void Expel();
		void Disable();
		
		enum {Pushing, Pulling, Nothing} pickupState;
		
		SpeedController *motor;
		SpeedController *angleMotor;
		
		double angleMotorSpeed, motorSpeed;
};

#endif
