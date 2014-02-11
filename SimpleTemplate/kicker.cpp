#include "kicker.h"
#include <Math.h>

Kicker::Kicker( SpeedController *kicker1_, SpeedController *kicker2_, DigitalInput *limitSwitchb_, DigitalInput *limitSwitchf_, Encoder *encoder_) {

                kicker1 = kicker1_;
                kicker2 = kicker2_;
				
				limitSwitchb = limitSwitchb_;
				limitSwitchf = limitSwitchf_;
				
				encoder = encoder_;
				
				kicker1->Set(0.0);
				kicker2->Set(0.0);
				
				isKicking = false;
				isPullingBack = false;
				isSitting = false;
				
				t = new Timer();
				t->Start();

}
	
void Kicker::Actuate() {
	if (isPullingBack) {
		kicker1->Set(-1.0);
		kicker2->Set(-1.0);
		if (t->Get() >= 1.25) {
			t->Reset();
			isPullingBack = false;
			isSitting = true;
		}
	}else if (isSitting){
	 kicker1->Set(0);
	 kicker2->Set(0);
	 if (t->Get() >= 0.05) {
		 t->Reset();
		 isSitting = false;
		 isKicking = true;
	 }
	}else if (isKicking) {
		kicker1->Set(1.0);
		kicker2->Set(1.0);
		if (t->Get() >= 0.75) {
			isKicking = false;
			isRetracting = true;
			kicker1->Set(0);
			kicker2->Set(0);
			t->Reset();
		}
	}else if (isRetracting){
		kicker1->Set(-1);
		kicker2->Set(-1);
		if (t->Get() >= 0.35) {
			isRetracting = false;
			kicker1->Set(0);
			kicker2->Set(0);
			t->Reset();
		}
	}else {
		kicker1->Set(0.0);
		kicker2->Set(0.0);
	}
}

void Kicker::KickBall(){
	t->Reset();
	isPullingBack = true;
}

void Kicker::KickBallN() {
	t->Reset();
	isKicking = true;
}

void Kicker::Disable() {
	kicker1->Set(0);
	kicker2->Set(0);
}
