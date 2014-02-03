#include "pickup.h"
#include <Math.h>

Pickup::Pickup( SpeedController *motor_, SpeedController *angleMotor_ ) {

	motor = motor_;
	angleMotor = angleMotor_;
	angleMotorSpeed = 0.0;
	motorSpeed = 0.0;
                
}

void Pickup::Actuate() {
	motor->Set(motorSpeed);
	angleMotor->Set(angleMotorSpeed);
}

void Pickup::Disable() {
	angleMotorSpeed = 0.0;
	motorSpeed = 0.0;
	angleMotor->Set(0.0);
	motor->Set(0.0);
}

void Pickup::RunIntake(double wheelSpeed) {
	motorSpeed = wheelSpeed;
}

void Pickup::ArmAngle(double upMotorSpeed) {
	angleMotorSpeed = upMotorSpeed;
}

void Pickup::Raise() {
	angleMotorSpeed = 0.5;
}

void Pickup::Lower() {
	angleMotorSpeed = -0.5;
}

void Pickup::Intake() {
	motorSpeed = 0.5;
}

void Pickup::Expel() {
	motorSpeed = -0.5;
}