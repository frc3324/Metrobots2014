#include "kicker.h"
#include <Math.h>

Kicker::Kicker( SpeedController *kicker1_, SpeedController *kicker2_, DigitalInput *limitSwitch_) {

                kicker1 = kicker1_;
                kicker2 = kicker2_;
				
				limitSwitch = limitSwitch_;
				
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
		if (limitSwitch->Get()) {
			state = Nothing;
		}
	} else if (state == Kicking) {
		kicker1->Set(-0.2);
		kicker2->Set(0.2);
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