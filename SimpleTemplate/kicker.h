#ifndef KICKER_H
#define KICKER_H

#include "WPILib.h"
#include <Math.h>
#include "util/metropidcontroller.h"

class Kicker {
	
	public:
		Kicker( SpeedController *kicker1, SpeedController *kicker2, DigitalInput *limitSwitchb, DigitalInput *limitSwitchf, Encoder *encoder);
		~Kicker(){};
		void KickBall();
		void Actuate();
		void Disable();
		void KickBallN();
		void PullUp();
		Timer* t;
		
		enum {Nothing, PullingBack, Kicking, Sitting, Retracting, Pull} state;
		//int state; // 0 = Nothing, 1 = Pulling Back, 2 = Kicking
		
		SpeedController *kicker1;
		SpeedController *kicker2;
		DigitalInput *limitSwitchb;
		DigitalInput *limitSwitchf;
		Encoder *encoder;
		
		static const int kickRotationMin = 0;	//dummy value
		static const int kickRotationMax = 10;	//dummy value3
		
		bool isKicking, isPullingBack, isSitting, isRetracting;
};

#endif
