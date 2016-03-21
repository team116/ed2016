#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include <WPILib.h>

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
//const int LEFTMOTOR = 1;
//const int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
//const int RANGE_FINDER_PORT = 1;
//const int RANGE_FINDER_MODULE = 1;

namespace RobotPorts
{
	//PDP
	const unsigned int PDP = 0;

	// digital inputs

	const unsigned int SHOOTER_HOME_SWITCH = 0;
	const unsigned int SHOOTER_WHEEL_TACH = 1;
	const unsigned int LEFT_ENCODER_A = 2;
	const unsigned int LEFT_ENCODER_B = 3;
	const unsigned int RIGHT_ENCODER_A = 4;
	const unsigned int RIGHT_ENCODER_B = 5;
	const unsigned int INTAKE_LIMIT = 6;
	const unsigned int BALL_PREP_CHECK_LIMIT = 7;



	// analog inputs
	const unsigned int INTAKE_ANGLE_ENCODER = 0;
	const unsigned int SHOOTER_ANGLE_ENCODER = 1;
	const unsigned int SHOOTER_AZIMUTH_ENCODER = 2;
	const unsigned int AUTONOMOUS_NAVX_A = 4;
	const unsigned int AUTONOMOUS_NAVX_B = 5;
	const unsigned int AUTONOMOUS_NAVX_C = 6;

	//motors
	const unsigned int RIGHT_FRONT_MOTOR = 0;
	const unsigned int RIGHT_BACK_MOTOR = 1;
	const unsigned int LEFT_FRONT_MOTOR = 2;
	const unsigned int LEFT_BACK_MOTOR = 3;

	const unsigned int WINCH_MOTOR_FRONT = 4;
	const unsigned int WINCH_MOTOR_BACK = 5;

	const unsigned int SHOOTER_MOTOR = 6;

	const unsigned int SHOOTER_PITCH_MOTOR = 8;
	const unsigned int SHOOTER_PUSH_MOTOR = 9;  //the holder wheels, the ball loader, theyre all the same thing

	//NAVX
	const unsigned int INTAKE_ROLLER_MOTOR = 10;//N0
	const unsigned int INTAKE_ANGLE_MOTOR = 11;//N1
	const unsigned int CLIMBER_ARMED_MOTOR = 12;//N2

	// I2C
	const unsigned int LIDAR_ADDRESS = 0x62;
	const unsigned int LIDAR_INIT_REGISTER = 0x00;
	const unsigned int LIDAR_RANGE_REGISTER = 0x8f;

}

namespace OI_Ports
{
	//Joysticks
	const unsigned int LEFT_JOYSTICK = 0;
	const unsigned int RIGHT_JOYSTICK = 1;
	const unsigned int BUTTONS_JOYSTICK1 = 2;
	const unsigned int BUTTONS_JOYSTICK2 = 3;

	const unsigned int B_DRIVE_ALIGN_BUTTON_LEFT = 2;
	const unsigned int B_DRVIE_ALIGN_BUTTON_RIGHT = 2;

	const unsigned int B_TURN_X_AXIS_RIGHT = 3;
	const unsigned int B_TURN_X_AXIS_LEFT = 3;

	// buttons joystick 1, digital
	const unsigned int AUTO_AIM_BUTTON = 1;
	const unsigned int SHOOT_BUTTON = 2;
	const unsigned int TEST_BUTTON = 3;
	const unsigned int CLEAR_COMMANDS_BUTTON = 4;

	const unsigned INTAKE_BELT_FORWARD_SWITCH = 6;
	const unsigned INTAKE_BELT_BACKWARD_SWITCH = 7;

	const unsigned SHOOTER_WHEELS_SWITCH = 9;

	const unsigned PID_TOGGLE_SWITCH = 5;

	// buttons joystick 1, analog
	const unsigned int MANUAL_AIM_DIAL = 0; // X
	const unsigned int SHOOTER_SPEED_DIAL = 1; // Y
	const unsigned int INTAKE_ANGLE_DIAL = 2; // Z

	// buttons joystick 2, digital
	const unsigned int EXTEND_SCALING_ARM_BUTTON = 1;
	const unsigned int RETRACT_SCALING_ARM_BUTTON = 2;
	const unsigned int AUTO_CLIMBER_DEPLOY_BUTTON = 3;
	const unsigned int AUTO_WINCH_BUTTON = 4;
	const unsigned int MANUAL_WINCH_ENABLE_SWITCH = 5;

	// buttons joystick 2, analog
	const unsigned int FRONT_WINCH_JOYSTICK = 0; // X
	const unsigned int BACK_WINCH_JOYSTICK = 1; // Y
}

namespace Utils
{
	enum VerticalDirection
	{
		UP,
		V_STILL,
		DOWN
	};
	enum HorizontalDirection
	{
		IN,
		H_STILL,
		OUT
	};
	enum RobotType
	{
		CAN_MOTOR_BOT,
		ED2016_BOT
	};
	RobotType getRobotType();
	SpeedController* constructMotor(unsigned int port);

	int voltageConversion(const float voltage, const int voltage_levels, const float max_voltage);
	float boundaryCheck(float target, float min, float max);
	float deadZoneCheck(float axis, float offset);

}


#endif
