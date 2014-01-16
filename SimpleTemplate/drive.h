#ifndef DRIVE_H
#define DRIVE_H

#include "WPILib.h"
#include <Math.h>
#include "util/metropidcontroller.h"

class Drive {

	public:
		Drive( SpeedController *flMotor_, SpeedController *blMotor_, SpeedController *frMotor_, SpeedController *brMotor_, 
				Encoder *flEncoder_, Encoder *blEncoder_, Encoder *frEncoder_, Encoder *brEncoder_, 
				Gyro *gyro_ );
		~Drive(){};
		void Actuate();
		void Disable();
		void SetMecanumXYTurn( double x, double y, double turn );
		void SetMecanumRLStrafe( double leftSide, double rightSide, double strafe );
		void SetHoldAngle( bool isOn );
		void SetTargetAngle( double degrees );
		double GetDistMoved();
		void ResetEncoders();
		void ResetGyro( double bias = 0.0 );
		double GetGyroAngle();
		bool IsFieldOriented();
		void SetFieldOriented( bool value );
		void SetPIDControl( bool value );
		bool IsPIDControl();
		bool IsSlowDrive();
		void SetSlowDrive( bool value );
		void SetInvertedMotors( bool fl, bool bl, bool fr, bool br );
		
		static const double PID_P = 1.0;
		static const double PID_I = 0.0;
		static const double PID_D = 0.1;
		
		static const double XYTURN_PID_P = 1.0;
		static const double XYTURN_PID_I = 0.0;
		static const double XYTURN_PID_D = 0.1;
		
		static const double VEL_PID_MULTIPLIER = 1600;
		
		static const double ANGLE_P = -1.0/45.0; 
		static const double AIM_BIAS_INCREMENT = 20.0;
		
		static const double SLOW_DRIVE_MULTIPLIER = 0.4;
		Encoder *flEncoder, *blEncoder, *frEncoder, *brEncoder;

	//private:
		void NormalizeMotorSpeeds();
	
		SpeedController *flMotor, *blMotor, *frMotor, *brMotor;
		Gyro *gyro;
		MetroPIDController *flPID, *blPID, *frPID, *brPID, *xPID, *yPID, *turnPID;
		
		double driverX, driverY, driverTurn, targetAngle;
		int motorInverters[4];
		double gyroBias;
		
		bool isPIDControl;
		bool isSlowDrive;
		bool isHoldAngle;
		bool isFieldOriented;

};

#endif
