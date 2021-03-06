#include "pickup.h"
#include <Math.h>

Pickup::Pickup( SpeedController *motor_, DualRelay *angleMotor_, DigitalInput *bottomSwitch_, DigitalInput *topSwitch_ ) {

	motor = motor_;
	angleMotor = angleMotor_;
	bottomSwitch = bottomSwitch_;
	topSwitch = topSwitch_;
	angleMotorBool = Relay::kOff;
	motorSpeed = 0.0;
	
	pickupState = Nothing;
	angleState = Stopped;
                
}

void Pickup::Actuate() {
	//motor->Set(motorSpeed);
	/*if ( !topSwitch->Get() || !bottomSwitch->Get() ){
		angleMotor->Set(Relay::kOff);
	}else{
		angleMotor->Set(angleMotorBool);
	}*/
	
	if( pickupState == Pushing ){
		motor->Set(1);
	}else if( pickupState == Pulling ){
		motor->Set(-1);
	}else{
		motor->Set(0);
	}
	
	if(( angleState == Up  || pickupState == Kicking ) && topSwitch->Get() ) {
		angleMotor->Set(Relay::kReverse);
	}else if ( angleState == Down && bottomSwitch->Get() ) {
		angleMotor->Set(Relay::kForward);
	}else{
		angleMotor->Set(Relay::kOff);
		angleState = Stopped;
		moveAllWay = false;
	}
	
	
}

void Pickup::Disable() {
	motorSpeed = 0.0;
	angleMotor->Set(Relay::kOff);
	motor->Set(0.0);
	angleState = Stopped;
}

void Pickup::RunIntake(double wheelSpeed) {
	motorSpeed = wheelSpeed * 0.85;
}


void Pickup::Raise() {
	angleMotorBool = Relay::kReverse;
	angleState = Up;
	moveAllWay = false;
}

void Pickup::Lower() {
	angleMotorBool = Relay::kForward;
	angleState = Down;
	moveAllWay = false;
}

void Pickup::ToTop() {
	angleMotorBool = Relay::kReverse;
	angleState = Up;
	moveAllWay = true;
}

void Pickup::ToBottom() {
	angleMotorBool = Relay::kForward;
	angleState = Down;
	moveAllWay = true;
}

void Pickup::StopAngle() {
	angleMotorBool = Relay::kOff;
	angleState = Stopped;
}

void Pickup::Intake() {
	pickupState = Pulling;
}

void Pickup::Expel() {
	pickupState = Pushing;
}

void Pickup::Kick() {
	pickupState = Kicking;
	moveAllWay = true;
}

void Pickup::StopIntake() {
	pickupState = Nothing;
}

bool Pickup::AllWay() {
	if ( moveAllWay ) return 1;
	else return 0;
}

bool Pickup::isKicking() {
	if ( pickupState == Kicking ) return 1;
	else return 0;
}
