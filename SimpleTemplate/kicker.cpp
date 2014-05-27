#include "kicker.h"
#include <Math.h>

Kicker::Kicker( SpeedController *kicker1_, SpeedController *kicker2_, AnalogChannel *kickerPot_) {

                kicker1 = kicker1_;
                kicker2 = kicker2_;
				
                //TODO: add GetAdjustedPotValue() method
				kickerPot = kickerPot_;
				
				state = Nothing;
				
				kicker1->Set(0.0);
				kicker2->Set(0.0);
				
				isKicking = false;
				isPullingBack = false;
				isSitting = false;
				
				t = new Timer();
				t->Start();

}
	
void Kicker::Actuate() {
	if (state == PullingBack) {
		kicker1->Set(1.0);
		kicker2->Set(1.0);
		if (t->Get() >= 0.4) {
			t->Reset();
			state = Kicking;
		}
	}else if (state == Kicking) {
		kicker1->Set(-1.0);
		kicker2->Set(-1.0);
		if (kickerPot->GetValue() > (kickerPotVal + 670)) {
			state = Retracting;
			kicker1->Set(0);
			kicker2->Set(0);
			t->Reset();
		}
	}else if (state == Retracting){
		kicker1->Set(0.4);
		kicker2->Set(0.4);
		if (kickerPot->GetValue() < (kickerPotVal + 90)) {
			state = Nothing;
			kicker1->Set(0);
			kicker2->Set(0);
			t->Reset();
		}
	}else if (state == Pull){
		kicker1->Set(1);
		kicker2->Set(1);
		if (kickerPot->GetValue() >= 1) {
			kicker1->Set(-0.5);
			kicker2->Set(-0.5);
			if (kickerPot->GetValue() >= 1) {
				kicker1->Set(0);
				kicker2->Set(0);
			}
		}
	}else if (state == Raising){
		kicker1->Set(1);
		kicker2->Set(1);
	}else if (state == Nothing && kickerPot->GetValue() > (kickerPotVal + 15)){
		kicker1->Set(0.8);
		kicker2->Set(0.8);
	}
	else {
		kicker1->Set(0.0);
		kicker2->Set(0.0);
	}
}

void Kicker::KickBall(){
	if (state == Nothing) {
		t->Reset();
		state = PullingBack;
	}
}

void Kicker::KickBallN() {
	if (state == Nothing) {
		//encoder->Reset();
		t->Reset();
		state = Kicking;
	}
}

void Kicker::PullUp() {
	if (state == Nothing) {
		state = Pull;
	}
}

void Kicker::RaiseLeg() {
	if (state == Nothing) {
		state = Raising;
	}
}

void Kicker::StopRaise() {
	if (state == Raising) state = Nothing;
}

void Kicker::Disable() {
	kicker1->Set(0);
	kicker2->Set(0);
	state = Nothing;
}

bool Kicker::State() {
	if (state == Nothing) return false;
	else return true;
}

void Kicker::KickerPotVal(int x) {
	kickerPotVal = x;
}
