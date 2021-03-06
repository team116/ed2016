/*
 * DriveStraight.h
 *
 *  Created on: Feb 18, 2016
 *      Author: amanzeb
 */

#ifndef SRC_COMMANDS_DRIVESTRAIGHT_H_
#define SRC_COMMANDS_DRIVESTRAIGHT_H_
#include <CommandBase.h>
#include <Subsystems/Sensors.h>
#include "WPILib.h"
#include "OI.h"

class DriveStraight : public CommandBase
{
public:
	enum JoystickSide
	{
		LEFT = 1,
		RIGHT = 2
	};
	enum SensorType
	{
		GYRO,
		ENCODER
	};

	DriveStraight(JoystickSide, SensorType);
	DriveStraight(float, SensorType, float timeout = -1.0);
	void Initialize ();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();


private:
	bool interrupted;
	float timeout;

	float curr_left_speed;
	float curr_right_speed;
	JoystickSide joystick_used;
	SensorType sensor_type;

	static const float MAX_ROBOT_SPEED;
	float joystick_value;
	static const float ENCODER_SPEED_OFFSET;

	float starting_robot_angle;
	static const float DEGREE_TOLERANCE;
	static const float GYRO_SPEED_OFFSET;
};






#endif /* SRC_COMMANDS_DRIVESTRAIGHT_H_ */
