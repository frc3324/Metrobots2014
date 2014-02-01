#include "kicker.h"
#include <Math.h>

Kicker::Kicker( SpeedController *kicker1_, SpeedController *kicker2_, DigitalInput *limitSwitchb_, DigitalInput *limitSwitchf_, Encoder *encoder_) {

                kicker1 = kicker1_;
                kicker2 = kicker2_;
				
				limitSwitchb = limitSwitchb_;
				limitSwitchf = limitSwitchf_
				
				encoder = encoder_;
				
				state = Nothing;
                
}

void Kicker::PullBackKicker() {
        state = PullingBack;
        //kicker1->Set(-1.0);
		//kicker2->Set(1.0);
}

void Kicker::Actuate() {
	if (state == PullingBack) {
		kicker1->Set(0.0);
		kicker2->Set(0.0);
		if (limitSwitchb->Get() || encoder->Get() <= kickRotationMin) {
			state = Nothing;
		}
	} else if (state == Kicking) {
		kicker1->Set(-0.2);
		kicker2->Set(0.2);
		if (limitSwitchf->Get() || encoder->Get() >= kickRotationMax) {
			state = Nothing;
		}
	}
	} else if (state == Nothing) {
		kicker1->Set(0.0);
		kicker2->Set(0.0);
	}
}

void Kicker::KickBall() {
        state = Kicking;
        //kicker1->Set(-0.2);
		//kicker2->Set(0.2);
        
}

void Kicker::Disable() {
		state = Nothing;
		//kicker1->Set(0);
		//kicker2->Set(0);
}