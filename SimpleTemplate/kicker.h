#ifndef KICKER_H
#define KICKER_H

#include "WPILib.h"
#include <Math.h>
#include "util/metropidcontroller.h"

class Kicker {

	public:
		Kicker( SpeedController *kicker1, SpeedController *kicker2);
		~Kicker(){};
		void PullBackKicker();
		void KickBall();
		
		SpeedController *kicker1;
		SpeedController *kicker2;
};

#endif
