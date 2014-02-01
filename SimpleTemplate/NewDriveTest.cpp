#include "WPILib.h"

class RobotDemo : public SimpleRobot
{
	RobotDrive: myRobot;
	Joystick stick;
	
public:
	RobotDemo(void):
		myRobot(1, 2, 3, 4),
		stick(1)
	{
		myRobot.SetExpiration(0.1)
	}
	
	void OperatorControl(void)
	{
		myRobot.SetSafteyEnabled(true);
		while (IsOperatorControl())
		{
			myRobot.ArcadeDrive(stick);
			Wait(0.005);
		}
	}
};

START_ROBOT_CLASS(RobotDemo);