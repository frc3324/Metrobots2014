#include "WPILib.h"

#include "util/gamepad.h"
#include "util/metropidcontroller.h"
#include "util/dualrelay.h"
#include "drive.h"
#include "kicker.h"
#include "pickup.h"
#include <stdio.h>
#include <Math.h>

class CommandBasedRobot : public IterativeRobot {
	private:
        
        typedef enum {Kick, DoubleKick, Forward, NoScript} AutonScript;
        AutonScript script;
        int step;
        Timer *timer, *freshness;
        
        Talon *flMotor, *blMotor, *frMotor, *brMotor, *kicker1, *kicker2, *pickupMotor, *angleMotor;
        DigitalInput *limitSwitchf, *limitSwitchb;
        Encoder *flEncoder, *blEncoder, *frEncoder, *brEncoder, *kickerEncoder;
        Gyro *gyro;
        GamePad *driverGamePad, *kickerGamePad;
        
        Drive *drive;
		Kicker *kicker;
		Pickup *pickup;
        
        DriverStationLCD *ds;
        //NetworkTable *table;
        
        int state;
        
        virtual void RobotInit() {
                
                flMotor = new Talon( 1 );
                blMotor = new Talon( 2 );
                frMotor = new Talon( 3 );
                brMotor = new Talon( 4 );
				kicker1 = new Talon( 5 );
				kicker2 = new Talon( 6 );
				pickupMotor = new Talon( 7 );
				angleMotor = new Talon( 8 );
							
                timer = new Timer();
                freshness = new Timer();

                limitSwitchb = new DigitalInput( 1 );
                limitSwitchf = new DigitalInput( 2 );
                
                flEncoder = new Encoder( 9, 10 );
                blEncoder = new Encoder( 11, 12 );
                frEncoder = new Encoder( 5, 6 );
                brEncoder = new Encoder( 7, 8 );
                kickerEncoder = new Encoder( 3, 4 );
                
                gyro = new Gyro( 1 );
                gyro->Reset();

                driverGamePad = new GamePad( 1 );
                kickerGamePad = new GamePad( 2 );
                
                
                drive = new Drive( flMotor, blMotor, frMotor, brMotor, flEncoder, blEncoder, frEncoder, brEncoder, gyro );
                drive->SetInvertedMotors( false, false, true, true );
                
                kicker = new Kicker( kicker1, kicker2, limitSwitchb, limitSwitchf, kickerEncoder );
                pickup = new Pickup( pickupMotor, angleMotor );
                

                
                ds = DriverStationLCD::GetInstance();

                //table = NetworkTable::GetTable("net");
                ////net->PutNumber("angle", 0.0);
                ////net->PutBoolean("hasAngle", 0.0);
                
                script = Forward;
                step = 0;
                timer->Reset();
                timer->Start();
                
                freshness->Reset();
                freshness->Start();
                
        }
        
        virtual void AutonomousInit() {
                Disable();
                step = 0;
                timer->Reset();
                drive->ResetGyro();
        }

		void AdvanceStep() {
			step++;
			timer->Reset();
		}
        
        virtual void AutonomousPeriodic() {
			
			if (script == Kick) {
				switch (step) {
				case 0:
					kicker->KickBallN();
					if (timer->Get() >= 1.5) AdvanceStep();
					break;
				case 1:
					drive->SetMecanumXYTurn(0.0, 2.0/3.0, 0.0);
					if (timer->Get() >= 2) AdvanceStep();
					break;
				case 2:
					drive->SetMecanumXYTurn(0.0, 0.0, 0.0);
					break;
				}
				//drive->SetPIDControl( true );
			}else if (script == DoubleKick) {
				switch (step) {
				case 0:
					kicker->KickBallN();
					if (timer->Get() >= 1) AdvanceStep();
					break;
				case 1:
					drive->SetMecanumXYTurn(0.0, 2.0/3.0, 0.0);
					pickup->RunIntake(-1);
					if (timer->Get() >= 0.5) AdvanceStep();
					break;
				case 2:
					drive->SetMecanumXYTurn(0.0, 0.0, 0.0);
					pickup->ArmAngle(1);
					if (timer->Get() >= 0.5) AdvanceStep();
					break;
				case 3:
					pickup->ArmAngle(0);
					kicker->KickBallN();
					break;
				}
				//drive->SetPIDControl( true );
			}else if (script == Forward) {
				switch (step) {
				case 0:
					drive->SetMecanumXYTurn(0.0, 2.0/3.0, 0.0);
					if (timer->Get() >= 1.5) AdvanceStep();
					break;
				case 1:
					drive->SetMecanumXYTurn(0.0, 0.0, 0.0);
					break;
				}
				//drive->SetPIDControl( true );
			}
			
			Actuate();
			PrintToDS();
			
		}
        
		
        
			virtual void TeleopInit() {
			                
			        drive->SetFieldOriented(true);
			                
			}
			
			virtual void TeleopPeriodic() {
 
                UpdateOI();
                
                /*
* Reset Gyro
* A: Press to reset gyro
*/
                if( driverGamePad->GetButton( GamePad::A ) ){
                        drive->ResetGyro();
                }
                
                /*
* Slow Drive
* LB or RB: Hold to toggle ON, Release to toggle OFF
*/
                drive->SetSlowDrive( driverGamePad->GetButton( GamePad::LB ) || driverGamePad->GetButton( GamePad::RB ) );
                
                /*
* Field Oriented
* START: Press to toggle ON
* BACK: Press to toggle OFF
*/
                drive->SetFieldOriented( driverGamePad->GetButtonDown( GamePad::START ) ? true : ( driverGamePad->GetButtonDown( GamePad::BACK ) ? false : drive->IsFieldOriented() ) );
                
                /*
* PID Control
* X: Press to toggle ON
* Y: Press to toggle OFF
*/
                drive->SetPIDControl( driverGamePad->GetButtonDown( GamePad::X ) ? true : ( driverGamePad->GetButtonDown( GamePad::Y ) ? false : drive->IsPIDControl() ) );

                /*
* Mecanum Drive
* LEFT_X_AXIS: Strafe Left/Right
* LEFT_Y_AXIS: Forward/Reverse
* RIGHT_X_AXIS: Turn
*/

                drive->SetMecanumXYTurn( driverGamePad->GetAxis( GamePad::LEFT_X ), driverGamePad->GetAxis( GamePad::LEFT_Y ), driverGamePad->GetAxis( GamePad::RIGHT_X ) );
                //drive->SetMecanumRLStrafe( driverGamePad->GetAxis( GamePad::LEFT_Y ), driverGamePad->GetAxis( GamePad::RIGHT_Y ), 0);
                        
                /*
* Hold Angle
* RIGHT_JS_BUTTON: Hold to hold current angle
* B: Hold to hold vision target angle
*/
                if( driverGamePad->GetButtonDown( GamePad::RIGHT_JS ) ){
                        drive->SetTargetAngle( drive->GetGyroAngle() );
                }
                if( driverGamePad->GetButton/*Down*/( GamePad::B ) ){
                        drive->SetTargetAngle( HasTarget() ? GetAbsoluteAngle() : drive->GetGyroAngle() );
                }
                drive->SetHoldAngle( driverGamePad->GetButton( GamePad::RIGHT_JS ) || driverGamePad->GetButton( GamePad::B ) || driverGamePad->GetAxis(GamePad::DPAD_X) != 0.0 );

                if(driverGamePad->GetDPadLeftDown()){
                        drive->SetTargetAngle( drive->GetGyroAngle() - Drive::AIM_BIAS_INCREMENT);
                }
                if(driverGamePad->GetDPadRightDown()){
                        drive->SetTargetAngle( drive->GetGyroAngle() + Drive::AIM_BIAS_INCREMENT);
                }
                
                if( kickerGamePad->GetButton( GamePad::A )) {
                	kicker->KickBallN();
                }
                
                if( kickerGamePad->GetButton( GamePad::X )) {
                	flEncoder->Reset();
                	blEncoder->Reset();
                	frEncoder->Reset();
                	brEncoder->Reset();
                }
                
                pickup->ArmAngle( kickerGamePad->GetAxis( GamePad::LEFT_Y ));

                pickup->RunIntake( kickerGamePad->GetAxis( GamePad::RIGHT_Y ));

                
                Actuate();
                PrintToDS();
                
			}
        
        virtual void DisabledInit() {
                
                Disable();
                
        }
        
        virtual void DisabledPeriodic() {
                
                UpdateOI();
					
                if (driverGamePad->GetButton( GamePad::A )) {
					script = Kick;
				}else if (driverGamePad->GetButton( GamePad::B )) {
					script = DoubleKick;
				}else if (driverGamePad->GetButton( GamePad::X )) {
					script = Forward;
				}
                
                drive->SetPIDControl( driverGamePad->GetButtonDown( GamePad::X ) ? true : ( driverGamePad->GetButtonDown( GamePad::Y ) ? false : drive->IsPIDControl() ) );
                
                drive->SetFieldOriented( driverGamePad->GetButtonDown( GamePad::START ) ? true : ( driverGamePad->GetButtonDown( GamePad::BACK ) ? false : drive->IsFieldOriented() ) );
                
                if( kickerGamePad->GetButton( GamePad::X )) {
                		flEncoder->Reset();
                		blEncoder->Reset();
                		frEncoder->Reset();
                		brEncoder->Reset();
                }

                PrintToDS();
                
        }
        
        void Actuate(){
                
                drive->Actuate();
                kicker->Actuate();
                pickup->Actuate();
        }
        
        void Disable(){
                
                drive->Disable();
                kicker->Disable();
                pickup->Disable();
        }
        
        void UpdateOI(){

                driverGamePad->Update();
                kickerGamePad->Update();
                IsFreshTarget();
                
        }
        
        void PrintToDS(){
                
                ds->Clear();
                ds->Printf(DriverStationLCD::kUser_Line1, 1, "Auto: %s", script == Kick ? "Single Kick" : ( script == DoubleKick ? "DoubleKick" : ( script == Forward ? "Forward" :( script == NoScript ? "None" : "YOU BROKE IT" ) ) ) );
                ds->Printf(DriverStationLCD::kUser_Line2, 1, "Dr: %s%s%f", drive->IsPIDControl() ? "PID, " : "", drive->IsFieldOriented() ? "FO, " : "", drive->GetGyroAngle() );
                ds->Printf(DriverStationLCD::kUser_Line3, 1, "Vi: %s, Fresh: %f", HasTarget() ? "Y" : "N", freshness->Get() );
                ds->Printf(DriverStationLCD::kUser_Line4, 1, "%f", flEncoder->Get() );
                ds->Printf(DriverStationLCD::kUser_Line4, 1, "%d : %d : %d : %d", flEncoder->Get(), blEncoder->Get(), frEncoder->Get(), brEncoder->Get() );
                ds->UpdateLCD();
                
        }
        
        double GetAbsoluteAngle() {
                return /*table->GetNumber("angle", 0.0) +*/ drive->GetGyroAngle();
        }
        
        double GetRelativeAngle() {
                return 0.0;//table->GetNumber("angle", 0.0);
        }
        
        bool HasTarget(){
                return false;//table->GetBoolean("hasTarget", false);
        }
        
        bool IsFreshTarget() {
                bool isFresh = false;//table->GetBoolean("isFresh", false);
                if(isFresh) {
                        freshness->Reset();
                }
                //table->PutBoolean("isFresh", false);
                return isFresh;
        }
        
        double AngleDiff( double angle1, double angle2 ){
                return fmod(angle1 - angle2 + 180.0, 360.0) - 180.0;
        }
	
};


START_ROBOT_CLASS(CommandBasedRobot);
