#include "WPILib.h"


class RobotDemo : public SimpleRobot
{
	RobotDrive myRobot; // Object for basic tank drive system
	Joystick gamepad; // Controller object referencing PS2 game pad controller 
	Solenoid ShiftHigh; //Solenoid object that actuates high gear
	Solenoid ShiftLow; //Solenoid object that actuates low gear
	Compressor Compress; // Object to add a compressor
	
public:
	RobotDemo(void): 
		myRobot(1, 2),	// Making ports 1 and 2 on digital IO side card responsible for drive motors.
		gamepad(1),		// PS2 gamepad is listed as first controller in drive station.
		ShiftHigh(3),	// Solenoids (splitter wire off of single output) for high gear on port 3 of solenoid card.
		ShiftLow(4),	// Solenoids for low gear on port 4 of solenoid card.
		Compress(1,1)	// Basic info for porting to compressor.
	{
		myRobot.SetExpiration(0.1);
		myRobot.SetSafetyEnabled (false);
	}

	void Autonomous() // No Auton code yet. Just controlling robot manually for now.
	{
	}

	void OperatorControl()
	{
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl())
		{
			Compress.Start(); //Starts up Compressor. No off code needed since pressure switch does the work.
			myRobot.TankDrive(gamepad.GetRawAxis(2), gamepad.GetRawAxis(4)); // drive tank style
			Wait(0.005);				// Motor update time.
			if(gamepad.GetRawButton(6)== true) // Referencing button 6 (bottem right trigger) on gamepad.
			{
				ShiftLow.Set (true);	// Shifts the robot drivetrain into low gear.
				ShiftHigh.Set (false);
			}
			if(gamepad.GetRawButton(8)== true) // Referencing button 8 (upper right trigger) on gamepad.
			{
				ShiftHigh.Set (true); // Shifts the robot drive train into high gear.
				ShiftLow.Set (false);
			}
		}
	}
	

	void Test() {

	}
};

START_ROBOT_CLASS(RobotDemo);

