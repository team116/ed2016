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
	enum SensorType
	{
		GYRO,
		ENCODER
	};

	DriveStraight(int, SensorType);
	void Initialize ();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();


private:
	float curr_left_speed;
	float curr_right_speed;
	int joystick_used;
	SensorType sensor_type;

	static const float MAX_ROBOT_SPEED;
	float joystick_value;
	static const float ENCODER_SPEED_OFFSET;

	float starting_robot_angle;
	static const float DEGREE_TOLERANCE;
	static const float GYRO_SPEED_OFFSET;
};






#endif /* SRC_COMMANDS_DRIVESTRAIGHT_H_ */