#include "pickup.h"
#include <Math.h>

Pickup::Pickup( SpeedController *motor_, DualRelay *angleMotor_ ) {

	motor = motor_;
	angleMotor = angleMotor_;
	angleMotorBool = Relay::kOff;
	motorSpeed = 0.0;
                
}

void Pickup::Actuate() {
	motor->Set(motorSpeed);
	angleMotor->Set(angleMotorBool);
}

void Pickup::Disable() {
	motorSpeed = 0.0;
	angleMotor->Set(Relay::kOff);
	motor->Set(0.0);
}

void Pickup::RunIntake(double wheelSpeed) {
	motorSpeed = wheelSpeed;
}

void Pickup::ArmAngle(double upMotorSpeed) {
	//angleMotorSpeed = upMotorSpeed;
}

void Pickup::Raise() {
	angleMotorBool = Relay::kReverse;
}

void Pickup::Lower() {
	angleMotorBool = Relay::kForward;
}

void Pickup::StopAngle() {
	angleMotorBool = Relay::kOff;
}

void Pickup::Intake() {
	motorSpeed = 0.5;
}

void Pickup::Expel() {
	motorSpeed = -0.5;
}
