#ifndef PICKUP_H
#define PICKUP_H

#include "WPILib.h"
#include <Math.h>
#include "util/metropidcontroller.h"
#include "util/dualrelay.h"

class Pickup {

	public:
		Pickup( SpeedController *motor, DualRelay *angleMotor, DigitalInput *bottomSwitch, DigitalInput *topSwitch );
		~Pickup(){};
		void Actuate();
		void RunIntake(double wheelSpeed);
		void Raise();
		void Lower();
		void ToTop();
		void ToBottom();
		void StopAngle();
		void Intake();
		void Expel();
		void StopIntake();
		void Disable();
		void Kick();
		bool AllWay();
		bool isKicking();
		
		enum {Pushing, Pulling, Kicking, Nothing} pickupState;
		enum {Up, Down, Stopped} angleState;
		
		SpeedController *motor;
		DualRelay *angleMotor;
		DigitalInput *bottomSwitch, *topSwitch;
		
		double motorSpeed;
		Relay::Value angleMotorBool;
		bool moveAllWay;
};

#endif
