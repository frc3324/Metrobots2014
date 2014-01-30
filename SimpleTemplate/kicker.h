#ifndef KICKER_H
#define KICKER_H

#include "WPILib.h"
#include <Math.h>
#include "util/metropidcontroller.h"

class Kicker {

	public:
		Kicker( SpeedController *kicker1, SpeedController *kicker2, DigitalInput *limitSwitch);
		~Kicker(){};
		void PullBackKicker();
		void KickBall();
		
		typedef enum {PullingBack, Nothing, Kicking} state;
		
		SpeedController *kicker1;
		SpeedController *kicker2;
		DigitalInput *limitSwitch;
};

#endif
