#include <cstdlib>
#include <OI.h>

OI* OI::INSTANCE = nullptr;

OI::OI()
{
	joystick_left = new Joystick(0);
	joystick_right = new Joystick(1);
	joystick2 = new Joystick(2);
	intake_in = new JoystickButton(joystick2,1);
	intake_out = new JoystickButton(joystick2,2);
	shoot = new JoystickButton(joystick2,3);
	aim_shooter_up = new JoystickButton(joystick2,4);
	aim_shooter_down = new JoystickButton(joystick2,5);
	extend_arm = new JoystickButton(joystick2,6);
	retrive_arm = new JoystickButton(joystick2,7);
	arm_claw_open_close = new JoystickButton(joystick2,8);
}
float OI::getJoystickLeftY()
{
	return joystick_left->GetY();
}
float OI::getJoystickRightY()
{
	return joystick_right->GetY();
}
Shooter::IntakeDirection OI::getIntakeDirection()
{
	if (intake_in->Get())
	{
		return Shooter::IntakeDirection::INTAKE_IN;
	}
	else if (intake_out->Get())
	{
		return Shooter::IntakeDirection::INTAKE_OUT;
	}
	else
	{
		return Shooter::IntakeDirection::INTAKE_STILL;
	}
}
OI* OI::getInstance()
{
	if (INSTANCE != nullptr)
	{
		INSTANCE = new OI();
	}
	return INSTANCE;
}
