#include <cstdlib>
#include <OI.h>
#include <Commands/IntakeDefault.h>
#include <Commands/SelectCamera.h>

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

	intake_in->WhenPressed(new IntakeDefault(Shooter::IntakeDirection::INTAKE_IN));
	intake_in->WhenReleased(new IntakeDefault(Shooter::IntakeDirection::INTAKE_STILL));
	intake_out->WhenPressed(new IntakeDefault(Shooter::IntakeDirection::INTAKE_OUT));
	intake_out->WhenReleased(new IntakeDefault(Shooter::IntakeDirection::INTAKE_STILL));
	// Process operator interface input here.

	JoystickButton* joy2_button1 = new JoystickButton(joystick2, 1);
	JoystickButton* joy2_button2 = new JoystickButton(joystick2, 2);

	joy2_button1->WhenPressed(new SelectCamera(0));
	joy2_button2->WhenPressed(new SelectCamera(1));
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
	if (INSTANCE == nullptr)
	{
		INSTANCE = new OI();
	}
	return INSTANCE;
}
