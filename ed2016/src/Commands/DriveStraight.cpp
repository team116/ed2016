#include <Commands/DriveStraight.h>
#include <Subsystems/Mobility.h>
#include <RobotMap.h>

const float DriveStraight::MAX_ROBOT_SPEED = 60.0;
const float DriveStraight::ENCODER_SPEED_OFFSET = .05;

const float DriveStraight::DEGREE_TOLERANCE = 1.0;
const float DriveStraight::GYRO_SPEED_OFFSET = 0.1;

DriveStraight::DriveStraight(JoystickSide joystick, SensorType type)
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
	if(joystick_used == JoystickSide::LEFT)
	{
		joystick_value = oi -> getJoystickLeftY();
	}
	else if (joystick_used == JoystickSide::RIGHT)
	{
		joystick_value = oi ->getJoystickRightY();
	}

	switch(sensor_type)
	{
		case GYRO:
		{
			float degrees_off = (starting_robot_angle - sensors->robotAngle()) * -1;
			while(degrees_off > 180) {
				degrees_off -= 360;
			}
			while(degrees_off < -180) {
				degrees_off += 360;
			}

			if(degrees_off > DEGREE_TOLERANCE)
			{
				mobility->setLeft(Utils::boundaryCheck(joystick_value - (GYRO_SPEED_OFFSET * fabs(degrees_off)),-1.0, 1.0));
				mobility->setRight(Utils::boundaryCheck(joystick_value + (GYRO_SPEED_OFFSET * fabs(degrees_off)), -1.0, 1.0));
			}
			else if(degrees_off < -DEGREE_TOLERANCE)
			{
				mobility->setLeft(Utils::boundaryCheck(joystick_value + (GYRO_SPEED_OFFSET * fabs(degrees_off)), -1.0, 1.0));
				mobility->setRight(Utils::boundaryCheck(joystick_value - (GYRO_SPEED_OFFSET * fabs(degrees_off)), -1.0, 1.0));
			}
			else {
				mobility->setLeft(joystick_value);
				mobility->setRight(joystick_value);
			}
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
