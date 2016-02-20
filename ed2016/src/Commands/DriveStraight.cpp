#include <Commands/DriveStraight.h>
#include <Subsystems/Mobility.h>

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
void DriveStraight::Interupted()
{

}
DriveStraight::~DriveStraight()
{
	// TODO Auto-generated destructor stub
}

