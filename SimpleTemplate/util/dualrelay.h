#ifndef DUAL_RELAY_H
#define DUAL_RELAY_H

#include "WPILib.h"

class DualRelay {
	public:
		DualRelay( int forwardPort, int reversePort );
		~DualRelay(){};
		
		void Set( Relay::Value value );
	private:
		Relay *forward;
		Relay *reverse;
};


#endif
