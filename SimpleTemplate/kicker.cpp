#include "kicker.h"
#include <Math.h>

Kicker::Kicker( SpeedController *kicker1_, SpeedController *kicker2_, DigitalInput *limitSwitchb_, DigitalInput *limitSwitchf_, Encoder *encoder_) {

                kicker1 = kicker1_;
                kicker2 = kicker2_;
				
				limitSwitchb = limitSwitchb_;
				limitSwitchf = limitSwitchf_;
				
				encoder = encoder_;
				
				state = Nothing;
				
				kicker1->Set(0.0);
				kicker2->Set(0.0);
				
				encoder->Start();
				
				isKicking = false;
				isPullingBack = false;
				isSitting = false;
				
				t = new Timer();
				t->Start();

}
	
void Kicker::Actuate() {
	if (state == PullingBack) {
		kicker1->Set(-1.0);
		kicker2->Set(-1.0);
		if (t->Get() >= 1.25) {
			t->Reset();
			state = Sitting;
		}
	}else if (state == Sitting){
	 kicker1->Set(0);
	 kicker2->Set(0);
	 if (t->Get() >= 0.05) {
		 t->Reset();
		 state = Kicking;
	 }
	}else if (state == Kicking) {
		kicker1->Set(1.0);
		kicker2->Set(1.0);
		if (t->Get() >= 0.75) {
			state = Retracting;
			kicker1->Set(0);
			kicker2->Set(0);
			t->Reset();
		}
	}else if (state == Retracting){
		kicker1->Set(-1);
		kicker2->Set(-1);
		if (t->Get() >= 0.35) {
			state = Nothing;
			kicker1->Set(0);
			kicker2->Set(0);
			t->Reset();
		}
	}else if (state == Pull){
		kicker1->Set(1);
		kicker2->Set(1);
		if (encoder->Get() >= 1) {
			kicker1->Set(-0.5);
			kicker2->Set(-0.5);
			if (encoder->Get() >= 1) {
				kicker1->Set(0);
				kicker2->Set(0);
			}
		}
	}else {
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

void Kicker::Disable() {
	kicker1->Set(0);
	kicker2->Set(0);
}
