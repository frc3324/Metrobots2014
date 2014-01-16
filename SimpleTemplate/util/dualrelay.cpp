#include "dualrelay.h"
#include "WPILib.h"

DualRelay::DualRelay( int forwardPort, int reversePort ){
	
	forward = new Relay( forwardPort, Relay::kForwardOnly );
	reverse = new Relay( reversePort, Relay::kReverseOnly );

}

void DualRelay::Set( Relay::Value value )
{
	if( value == Relay::kForward )
	{
		forward->Set( Relay::kOn );
		reverse->Set( Relay::kOff );
	}
	else if( value == Relay::kReverse )
	{
		forward->Set( Relay::kOff );
		reverse->Set( Relay::kOn );
	}
	else if( value == Relay::kOff )
	{
		forward->Set( Relay::kOff );
		reverse->Set( Relay::kOff );
	}
}
