#include <Commands/DriveStraight.h>
#include <Subsystems/Mobility.h>
const float DriveStraight::MAX_ROBOT_SPEED = 60.0;
const float DriveStraight::ENCODER_SPEED_OFFSET = .05;

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
DriveStraight::~DriveStraight()
{
	// TODO Auto-generated destructor stub
}

