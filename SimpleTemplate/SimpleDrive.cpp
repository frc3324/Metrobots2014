#include "WPILib.h"

#include "util/gamepad.h"
#include "util/metropidcontroller.h"
#include "util/dualrelay.h"
#include "drive.h"
#include <stdio.h>
#include <Math.h>

class CommandBasedRobot : public IterativeRobot {
private:
	
        Talon *flMotor, *blMotor, *frMotor, *brMotor;
        GamePad *driverGamePad;
	
	virtual void RobotInit() {
				
				flMotor = new Talon( 1 );
				blMotor = new Talon( 2 );
				frMotor = new Talon( 3 );
				brMotor = new Talon( 4 );
				
                driverGamePad = new GamePad( 1 );
				
                drive = new Drive( flMotor, blMotor, frMotor, brMotor );
                drive->SetInvertedMotors( false, false, true, true );
				
	}
	
	virtual void TeleopPeriodic() {
		
				flMotor = driverGamePad->GetAxis ( GamePad::LEFT_Y ); 
				blMotor = driverGamePad->GetAxis ( GamePad::LEFT_Y );
				frMotor = driverGamePad->GetAxis ( GamePad::RIGHT_Y );
				brMotor = driverGamePad->GetAxis ( GamePad::RIGHT_Y );
		
	}
	
};

START_ROBOT_CLASS(CommandBasedRobot);