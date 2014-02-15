#ifndef PICKUP_H
#define PICKUP_H

#include "WPILib.h"
#include <Math.h>
#include "util/metropidcontroller.h"
#include "util/dualrelay.h"

class Pickup {

	public:
		Pickup( SpeedController *motor, DualRelay *angleMotor );
		~Pickup(){};
		void Actuate();
		void RunIntake(double wheelSpeed);
		void ArmAngle(double upMotorSpeed);
		void Raise();
		void Lower();
		void StopAngle();
		void Intake();
		void Expel();
		void Disable();
		
		enum {Pushing, Pulling, Nothing} pickupState;
		
		SpeedController *motor;
		DualRelay *angleMotor;
		
		double motorSpeed;
		Relay::Value angleMotorBool;
};

#endif
