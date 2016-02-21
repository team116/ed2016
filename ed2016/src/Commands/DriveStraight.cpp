#include <Commands/DriveStraight.h>
#include <Subsystems/Mobility.h>
#include <RobotMap.h>

const float DriveStraight::MAX_ROBOT_SPEED = 60.0;
const float DriveStraight::ENCODER_SPEED_OFFSET = .05;

const float DriveStraight::DEGREE_TOLERANCE = 1.0;
const float DriveStraight::GYRO_SPEED_OFFSET = 0.05;

DriveStraight::DriveStraight(int joystick, SensorType type)
{
	Requires(&*mobility);
	joystick_used = joystick;
	curr_left_speed = 0.0;
	curr_right_speed = 0.0;
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
		joystick_value = oi -> getJoystickLeftY();
	}
	else if (joystick_used == 1)
	{
		joystick_value = oi ->getJoystickRightY();
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
			curr_left_speed = sensors ->getSpeedLeft();
			curr_right_speed = sensors->getSpeedRight();
			float target_speed = MAX_ROBOT_SPEED * joystick_value;

			if(curr_left_speed > target_speed)
			{
				mobility ->setLeft(mobility ->getLeft() - ENCODER_SPEED_OFFSET);
			}

				else if(curr_left_speed < target_speed)
				{
					mobility ->setLeft(mobility ->getLeft() + ENCODER_SPEED_OFFSET);
				}

			if(curr_right_speed > target_speed)
			{
				mobility ->setRight(mobility ->getRight() - ENCODER_SPEED_OFFSET);
			}

				else if (curr_right_speed < target_speed)
				{
					mobility ->setRight(mobility ->getRight() + ENCODER_SPEED_OFFSET);
				}

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
