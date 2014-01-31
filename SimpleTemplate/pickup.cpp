#include "pickup.h"
#include <Math.h>

Pickup::Pickup( SpeedController *motor_, SpeedController *angleMotor_ ) {

                motor = motor_;
				angleMotor = angleMotor_;
                
}

void Pickup::Actuate() {
	
	if (pickupState == Pushing) {
		motor->Set(0.5);
	}
	if (pickupState == Pulling) {
		motor->Set(-0.5);
	}
	if (pickupState == Nothing) {
		motor->Set(0.0);
		angleMotor->Set(0.0);
	}
}

void Pickup::Disable() {
	pickupState = Nothing;
}

void Intake(double wheelSpeed) {
	motor->Set(wheelSpeed);
}

void ArmAngle(double upMotorSpeed) {
	angleMotor->Set(upMotorSpeed);
}