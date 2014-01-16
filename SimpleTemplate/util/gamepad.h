#ifndef GAME_PAD_H
#define GAME_PAD_H

#include "WPILib.h"
#define MAX_NUM_BUTTONS 12

class GamePad {

	public:
		GamePad( int port );
		double GetAxis( int axis );
		void Update();
		bool GetButton( int button );
		bool GetButtonDown( int button );
		bool GetButtonUp( int button );
		bool GetDPadLeftDown();
		bool GetDPadRightDown();

		static const double AXIS_DEADBAND = 0.10;
		
		static const int A = 1;
		static const int B = 2;
		static const int X = 3;
		static const int Y = 4;
		static const int LB = 5;
		static const int RB = 6;
		static const int BACK = 7;
		static const int START = 8;
		static const int LEFT_JS = 9;
		static const int RIGHT_JS = 10;
		
		static const int LEFT_X = 1;
		static const int LEFT_Y = 2;
		static const int TRIGGER = 3;
		static const int RIGHT_X = 4;
		static const int RIGHT_Y = 5;
		static const int DPAD_X = 6;
		static const int DPAD_Y = 7;
		
	private:
		Joystick *joystick_;
				
		bool oldBtnStates[ MAX_NUM_BUTTONS ];
		bool newBtnStates[ MAX_NUM_BUTTONS ];
		bool upEventStates[ MAX_NUM_BUTTONS ];
		bool downEventStates[ MAX_NUM_BUTTONS ];
		bool dPadLeftDownEvent;
		bool dPadRightDownEvent;
		bool dPadLeftOld;
		bool dPadRightOld;

};

#endif
