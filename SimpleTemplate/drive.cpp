#include "drive.h"
#include <Math.h>

Drive::Drive( SpeedController *flMotor_, SpeedController *blMotor_, SpeedController *frMotor_, SpeedController *brMotor_, 
                                Encoder *flEncoder_, Encoder *blEncoder_, Encoder *frEncoder_, Encoder *brEncoder_, 
                                Gyro *gyro_ ){

        flMotor = flMotor_;
        blMotor = blMotor_;
        frMotor = frMotor_;
        brMotor = brMotor_;
        
        flEncoder = flEncoder_;
        blEncoder = blEncoder_;
        frEncoder = frEncoder_;
        brEncoder = brEncoder_;

        flEncoder->Start();
        blEncoder->Start();
        frEncoder->Start();
        brEncoder->Start();
        
        gyro = gyro_;
        
        flPID = new MetroPIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, MetroPIDController::PID, true );
        blPID = new MetroPIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, MetroPIDController::PID, true );
        frPID = new MetroPIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, MetroPIDController::PID, true );
        brPID = new MetroPIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, MetroPIDController::PID, true );

        xPID = new MetroPIDController( Drive::XYTURN_PID_P, Drive::XYTURN_PID_I, Drive::XYTURN_PID_D, MetroPIDController::PID, true );
        yPID = new MetroPIDController( Drive::XYTURN_PID_P, Drive::XYTURN_PID_I, Drive::XYTURN_PID_D, MetroPIDController::PID, true );
        turnPID = new MetroPIDController( Drive::XYTURN_PID_P, Drive::XYTURN_PID_I, Drive::XYTURN_PID_D, MetroPIDController::PID, true );
        
        flPID->Disable();
        blPID->Disable();
        frPID->Disable();
        brPID->Disable();
        
        motorInverters[0] = 1;
        motorInverters[1] = 1;
        motorInverters[2] = 1;
        motorInverters[3] = 1;
        
        gyroBias = 0.0;
        
        isPIDControl = false;
        isSlowDrive = false;
        isFieldOriented = true;
        isHoldAngle = false;
        
        driverX = 0.0;
        driverY = 0.0;
        driverTurn = 0.0;
}

double clamp(double range, double num) {
        return (range > fabs(num)) ? 0.0 : num;
}

void Drive::Actuate(){

        flPID->SetSource( ( 1 / flEncoder->GetPeriod() ) / Drive::VEL_PID_MULTIPLIER );
        blPID->SetSource( ( 1 / blEncoder->GetPeriod() ) / Drive::VEL_PID_MULTIPLIER );
        frPID->SetSource( -( 1 / frEncoder->GetPeriod() ) / Drive::VEL_PID_MULTIPLIER );
        brPID->SetSource( -( 1 / brEncoder->GetPeriod() ) / Drive::VEL_PID_MULTIPLIER );

        double flVel = 1 / flEncoder->GetPeriod() / Drive::VEL_PID_MULTIPLIER;
        double blVel = 1 / flEncoder->GetPeriod() / Drive::VEL_PID_MULTIPLIER;
        double frVel = -1 / flEncoder->GetPeriod() / Drive::VEL_PID_MULTIPLIER;
        double brVel = -1 / flEncoder->GetPeriod() / Drive::VEL_PID_MULTIPLIER;

        xPID->SetSource( flVel + brVel - blVel - frVel );
        yPID->SetSource( flVel + brVel + blVel + frVel );
        turnPID->SetSource( flVel - brVel + blVel - frVel );
        
        double x = driverX;
        double y = driverY;
        double turn = driverTurn;


        double fl = ( y - x + turn ) * ( isSlowDrive ? Drive::SLOW_DRIVE_MULTIPLIER : 1.0 );
        double bl = ( y + x + turn ) * ( isSlowDrive ? Drive::SLOW_DRIVE_MULTIPLIER : 1.0 );
        double fr = ( y + x - turn ) * ( isSlowDrive ? Drive::SLOW_DRIVE_MULTIPLIER : 1.0 );
        double br = ( y - x - turn ) * ( isSlowDrive ? Drive::SLOW_DRIVE_MULTIPLIER : 1.0 );

        flMotor->Set( fl * motorInverters[0] );
        blMotor->Set( bl * motorInverters[1] );
        frMotor->Set( fr * motorInverters[2] );
        brMotor->Set( br * motorInverters[3] );

}

void Drive::Disable(){


        SetPIDControl( false );

        flMotor->Set( 0.0 );
        blMotor->Set( 0.0 );
        frMotor->Set( 0.0 );
        brMotor->Set( 0.0 );

}

void Drive::SetMecanumRLStrafe( double r, double l, double strafe ){

        driverX = strafe;
        driverY = (( r + l ) / 2) * (( r + l ) / 2);
        driverTurn = (( l - r ) / 2) * (( l - r ) / 2);

}

void Drive::SetMecanumXYTurn( double x, double y, double turn ){
        
        driverX = x;
        driverY = y;
        driverTurn = turn;

}


void Drive::SetFieldOriented( bool value ){

        isFieldOriented = value;

}

bool Drive::IsFieldOriented(){

        return isFieldOriented;

}

void Drive::SetHoldAngle( bool isOn ){

        isHoldAngle = isOn;

}

void Drive::SetTargetAngle( double degrees ){
        
        targetAngle = fmod( degrees, 360.0 );
        
}

void Drive::ResetEncoders(){

        flEncoder->Reset();
        blEncoder->Reset();
        frEncoder->Reset();
        brEncoder->Reset();

}

double Drive::GetDistMoved(){

        return ( flEncoder->Get() + blEncoder->Get() - frEncoder->Get() - brEncoder->Get() ) / 4;

}

void Drive::ResetGyro( double bias ){

        gyroBias = bias;
        gyro->Reset();

}

double Drive::GetGyroAngle(){

        return gyro->GetAngle() + gyroBias;

}

bool Drive::IsPIDControl(){

        return isPIDControl;

}

void Drive::SetPIDControl( bool value ){

        isPIDControl = value;
        
        if( isPIDControl ){
        
                flPID->Enable();
                blPID->Enable();
                frPID->Enable();
                brPID->Enable();

                xPID->Enable();
                yPID->Enable();
                turnPID->Enable();
        
        }
        else{
        
                flPID->Disable();
                blPID->Disable();
                frPID->Disable();
                brPID->Disable();
        
                xPID->Disable();
                yPID->Disable();
                turnPID->Disable();
                
        }

}

bool Drive::IsSlowDrive(){

        return isSlowDrive;

}

void Drive::SetSlowDrive( bool value ){

        isSlowDrive = value;

}

void Drive::SetInvertedMotors( bool fl, bool bl, bool fr, bool br ){

        motorInverters[0] = fl ? -1 : 1;
        motorInverters[1] = bl ? -1 : 1;
        motorInverters[2] = fr ? -1 : 1;
        motorInverters[3] = br ? -1 : 1;

}

void Drive::NormalizeMotorSpeeds(){
        
        /*double maxValue = 1.0;
                
        if(fabs( flSpeed ) > maxValue ){
                maxValue = fabs( flSpeed );
        }
        if( fabs( blSpeed ) > maxValue ){
                maxValue = fabs( blSpeed );
        }
        if( fabs( frSpeed ) > maxValue ){
                maxValue = fabs( frSpeed );
        }
        if( fabs( brSpeed ) > maxValue ){
                maxValue = fabs( brSpeed );
        }
        
        flSpeed = flSpeed / maxValue;
        blSpeed = blSpeed / maxValue;
        frSpeed = frSpeed / maxValue;
        brSpeed = brSpeed / maxValue;
        */
}