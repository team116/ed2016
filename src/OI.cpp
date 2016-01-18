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
	// Process operator interface input here.
}
float OI::GetJoystickLeftY()
{
	return joystick_left->GetY();
}
float OI::GetJoystickRightY()
{
	return joystick_right->GetY();
}
OI* OI::getInstance()
{
	if (INSTANCE != nullptr)
	{
		INSTANCE = new OI();
	}
	return INSTANCE;
}
