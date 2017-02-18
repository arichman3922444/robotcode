#ifndef ROBOT
#define ROBOT

#include "WPILib.h"
#include "CANTalon.h"
#include <cmath>
#include <AHRS.h>

// X-Box Controller Button IDs
#define BUTTON_A 1
#define BUTTON_B 2
#define BUTTON_X 3
#define BUTTON_Y 4
#define BUTTON_LB 5
#define BUTTON_RB 6
#define BUTTON_BACK 7
#define BUTTON_START 8
#define BUTTON_ANALOG_CLICK_LEFT 9
#define BUTTON_ANALOG_CLICK_RIGHT 10

// X-Box Controller Axis IDs
#define AXIS_ANALOG_LEFT_X 0
#define AXIS_ANALOG_LEFT_Y 1
#define AXIS_TRIGGER_LEFT 2
#define AXIS_TRIGGER_RIGHT 3
#define AXIS_ANALOG_RIGHT_X 4
#define AXIS_ANALOG_RIGHT_Y 5

// Global Functions
inline double dabs(double d) { return d > 0.0 ? d : -d; } // Absolute value of a double precision floating point number
inline bool IsReasonable(double axisVal) { return dabs(axisVal) > 0.2; } // Ensures the axis is intentionally engaged
inline float square(double num) { return num * num; } //Return the square of the the given number

// Constants
//const double WHEEL_DIAMETER = 6;

class Robot: public IterativeRobot
{
private:
    //Object Definitions
    CANTalon FrontLeftDrive;
    CANTalon BackLeftDrive;
    CANTalon FrontRightDrive;
    CANTalon BackRightDrive;
    RobotDrive DriveTrain;
    CANTalon GearSlide;
    CANTalon ClimbMotor;
    DoubleSolenoid LeftFlap;
    DoubleSolenoid RightFlap;
    Servo ClimbRelease;
    Joystick Driver;
    Joystick Operator;
  	Encoder GearEnc;
  	DigitalInput LeftBreakBeam;
  	DigitalInput RightBreakBeam;
    DigitalInput HaveGear;
    DigitalInput ActuateFlaps;
    DigitalInput LeftLimit;
    DigitalInput RightLimit;
    AHRS NavX;
    Ultrasonic FrontDist;
    Timer RobotTimer;

    cs::UsbCamera LifeCam;
    cs::CvSink VisionSink;

    double moveVal;
    double turnVal;
    double gearVal;

	bool isGearCentered;
	bool isGearScored;

	bool isVisionEnabled;
	bool XPrevState;

	bool LeftFlapState;
	bool RightFlapState;
	bool LBPrevState;
	bool RBPrevState;
	bool targetInSight;
	bool Automation;
	bool YPrevState;

public:
	Robot();
	void DisabledInit();
	void RobotInit();
	void AutonomousInit();
	void AutonomousPeriodic();
	void TeleopInit();
	void TeleopPeriodic();
	void TestInit();
	void TestPeriodic();

	void SetDriveMotors(float left, float right);
	void ArcadeDrive(float moveValue, float rotateValue, bool squaredInputs);
	void CylinderStateChange(DoubleSolenoid DS, short ID, bool ran);

	//Autonomous scoring with the camera
  	void ScoringSequence();
  	void DriveToPeg();

  	//NavX Helper Functions
  	void DriveRobot(double distance);
  	void TurnRobot(double angle);
  	double DistanceTraveled();
};
#endif