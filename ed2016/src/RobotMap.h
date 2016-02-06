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

#define ROBOT_TYPE ANDERSON_BOT

#if ROBOT_TYPE == ANDERSON_BOT
#define MOTOR_TYPE CANTalon
#elif ROBOT_TYPE == ED2016_BOT
#define MOTOR_TYPE VictorSP
#endif

namespace Robot
{
	// digital inputs

	const unsigned int LEFT_SHOOTER_WHEEL_TACH = 1;
	const unsigned int RIGHT_SHOOTER_WHEEL_TACH = 2;
	const unsigned int LEFT_ENCODER_A = 3;
	const unsigned int LEFT_ENCODER_B = 4;
	const unsigned int RIGHT_ENCODER_A = 5;
	const unsigned int RIGHT_ENCODER_B = 6;
	const unsigned int INTAKE_LIMIT = 7;
	const unsigned int BALL_PREP_CHECK_LIMIT = 8;


	// analog inputs
	const unsigned int SHOOTER_ANGLE_ENCODER = 0;
	const unsigned int INTAKE_ANGLE_ENCODER = 1;
	const unsigned int SHOOTER_AZIMUTH_ENCODER = 2;
	const unsigned int AUTONOMOUS_NAVX_A = 3;
	const unsigned int AUTONOMOUS_NAVX_B = 4;
	const unsigned int AUTONOMOUS_NAVX_C = 5;

	//motors
	const unsigned int LEFT_FRONT_MOTOR = 1;
	const unsigned int LEFT_BACK_MOTOR = 2;
	const unsigned int RIGHT_FRONT_MOTOR = 3;
	const unsigned int RIGHT_BACK_MOTOR = 4;


	const unsigned int INTAKE_ROLLER_MOTOR = 5;
	const unsigned int INTAKE_ANGLE_MOTOR = 6;

	const unsigned int LEFT_SHOOTER_MOTOR = 7;
	const unsigned int RIGHT_SHOOTER_MOTOR = 8;

	const unsigned int CLIMBER_ARMED_MOTOR = 9;

	const unsigned int SHOOTER_PITCH_MOTOR = 10;
	const unsigned int SHOOTER_PUSH_MOTOR = 11;

	const unsigned int WINCH_MOTOR_FRONT = 12;
	const unsigned int WINCH_MOTOR_BACK = 13;

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
	const unsigned int BUTTONS_JOYSTICK = 2;

	//Digital Buttons
	const unsigned int EXTEND_SCALING_ARM_BUTTON = 0;
	const unsigned int RETRACT_SCALING_ARM_BUTTON = 1;
	const unsigned int AUTO_WINCH_BUTTON = 2;
	const unsigned int SHOOTER_ENGAGE_BUTTON = 3;
	const unsigned int SHOOTER_DISENGAGE_BUTTON = 4;
	const unsigned int AUTO_AIM_BUTTON = 5;

	//Digital Switches
	const unsigned MANUAL_WINCH_ENABLE_SWITCH = 6;
	const unsigned SHOOTER_WHEELS_SWITCH = 7;
	const unsigned INTAKE_BELT_FORWARD_SWITCH = 8;
	const unsigned INTAKE_BELT_BACKWARD_SWITCH = 9;

	//Analog Dials
	const unsigned int INTAKE_ANGLE_DIAL = 0;
	const unsigned int SHOOTER_SPEED_DIAL = 1;
	const unsigned int MANUAL_AIM_DIAL = 2;

	//Analog Joysticks
	const unsigned int FRONT_WINCH_JOYSTICK = 4;
	const unsigned int BACK_WINCH_JOYSTICK = 5;
}

namespace Utils
{
	int voltageConversion(const float voltage, const int voltage_levels, const float max_voltage);
}

#endif
