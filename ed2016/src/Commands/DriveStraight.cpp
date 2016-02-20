#include <Commands/DriveStraight.h>
#include <Subsystems/Mobility.h>
#include <RobotMap.h>

//const float DriveStraight::STARTING_ROBOT_ANGLE = 5.0;
const float DriveStraight::DEGREE_TOLERANCE = 1.0;
const float DriveStraight::GYRO_SPEED_OFFSET = 0.05;

DriveStraight::DriveStraight(int joystick, SensorType type)
{
	Requires(&*mobility);
	joystick_used = joystick;
	curr_speed_left = 0.0;
	curr_speed_right = 0.0;
	sensor_type = type;
}

void DriveStraight::Initialize()
{
	starting_robot_angle = sensors->robotAngle();
}
void DriveStraight::Execute()
{
	if(joystick_used == 0)
	{
		mobility ->setStraight(oi -> getJoystickLeftY());
	}
	else if (joystick_used == 1)
	{
		mobility ->setStraight(oi ->getJoystickRightY());
	}

	switch(sensor_type)
	{
		case GYRO:
		{
			/*
			if(sensors->robotAngle()> (DEGREE_TOLERANCE + starting_robot_angle))
			{
				mobility->setLeft(Utils::boundryCheck(mobility->getLeft()-SPEED_OFFSET, -1.0, 1.0));

				mobility->setRight(Utils::boundryCheck(mobility->getRight()+SPEED_OFFSET, -1.0, 1.0));
			}
			else if(sensors->robotAngle() < (starting_robot_angle - DEGREE_TOLERANCE))
			{
				mobility->setLeft(Utils::boundryCheck(mobility->getLeft()+SPEED_OFFSET, -1.0, 1.0));
				mobility->setRight(Utils::boundryCheck(mobility->getRight()-SPEED_OFFSET, -1.0, 1.0));
			}*/
			break;
		}
		case ENCODER:
		{
			break;
		}
	}
}
bool DriveStraight::IsFinished()
{
	return false;
}
void DriveStraight::End()
{

}
void DriveStraight::Interrupted()
{

}
