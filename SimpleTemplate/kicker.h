#ifndef KICKER_H
#define KICKER_H

#include "WPILib.h"
#include <Math.h>
#include "util/metropidcontroller.h"

class Kicker {
	
	public:
		Kicker( SpeedController *kicker1, SpeedController *kicker2, AnalogChannel *kickerPot);
		~Kicker(){};
		void KickBall();
		void Actuate();
		void Disable();
		void KickBallN();
		void PullUp();
		void RaiseLeg();
		void StopRaise();
		bool State();
		void KickerPotVal(int x);
		int GetAdjustedPotValue();
		Timer* t;
		
		enum {Nothing, PullingBack, Kicking, Sitting, Retracting, Pull, Raising} state;
		//int state; // 0 = Nothing, 1 = Pulling Back, 2 = Kicking
		
		SpeedController *kicker1;
		SpeedController *kicker2;
		AnalogChannel *kickerPot;
		
		static const int kickRotationMin = 0;	//dummy value
		static const int kickRotationMax = 10;	//dummy value3
		
		bool isKicking, isPullingBack, isSitting, isRetracting;
		int kickerPotVal;
};

#endif
