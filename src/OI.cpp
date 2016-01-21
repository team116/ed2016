#include <cstdlib>
#include <Commands/IntakeDefault.h>
#include <Commands/SelectCamera.h>
#include <OI.h>

OI* OI::INSTANCE = nullptr;

OI::OI()
{
	// Process operator interface input here.

	//Instantiate Joysticks
	joystick_left = new Joystick(0);
	joystick_right = new Joystick(1);
	joystick_buttons = new Joystick(2);

	//Instantiate Joystick Left Buttons

	//Instantiate Joystick Right Buttons

	//Instantiate Joystick Buttons Buttons
	intake_in = new JoystickButton(joystick_buttons,1);
	intake_out = new JoystickButton(joystick_buttons,2);
	shoot = new JoystickButton(joystick_buttons,3);
	aim_shooter_up = new JoystickButton(joystick_buttons,4);
	aim_shooter_down = new JoystickButton(joystick_buttons,5);
	extend_arm = new JoystickButton(joystick_buttons,6);
	retrive_arm = new JoystickButton(joystick_buttons,7);
	arm_claw_open_close = new JoystickButton(joystick_buttons,8);
	select_camera_front = new JoystickButton(joystick_buttons, 9);
	select_camera_back = new JoystickButton(joystick_buttons, 10);

	//Set Joystick Left Events

	//Set Joystick Right Events

	//Set Joystick Buttons Events
	intake_in->WhenPressed(new IntakeDefault(Shooter::IntakeDirection::INTAKE_IN));
	intake_in->WhenReleased(new IntakeDefault(Shooter::IntakeDirection::INTAKE_STILL));
	intake_out->WhenPressed(new IntakeDefault(Shooter::IntakeDirection::INTAKE_OUT));
	intake_out->WhenReleased(new IntakeDefault(Shooter::IntakeDirection::INTAKE_STILL));


	// Process operator interface input here.

	JoystickButton* joy2_button1 = new JoystickButton(joystick_buttons, 1);
	JoystickButton* joy2_button2 = new JoystickButton(joystick_buttons, 2);

	joy2_button1->WhenPressed(new SelectCamera(0));
	joy2_button2->WhenPressed(new SelectCamera(1));
	select_camera_front->WhenPressed(new SelectCamera(Cameras::CameraDirection::FRONT));
	select_camera_back->WhenPressed(new SelectCamera(Cameras::CameraDirection::BACK));

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
