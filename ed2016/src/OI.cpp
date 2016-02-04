#include <cstdlib>
#include <Commands/RunIntake.h>
#include <Commands/SelectCamera.h>
#include <OI.h>

OI* OI::INSTANCE = nullptr;

OI::OI()
{
	//Instantiate Additional Analog Inputs
	intake_angle = new AnalogInput(OI_Ports::INTAKE_ANGLE_DIAL);
	shooter_speed = new AnalogInput(OI_Ports::SHOOTER_SPEED_DIAL);
	manual_aim = new AnalogInput(OI_Ports::MANUAL_AIM_DIAL);
	manual_front_winch = new AnalogInput(OI_Ports::FRONT_WINCH_JOYSTICK);
	manual_back_winch = new AnalogInput(OI_Ports::BACK_WINCH_JOYSTICK);

	//Instantiate Joysticks
	joystick_left = new Joystick(OI_Ports::LEFT_JOYSTICK);
	joystick_right = new Joystick(OI_Ports::RIGHT_JOYSTICK);
	joystick_buttons = new Joystick(OI_Ports::BUTTONS_JOYSTICK);

	//Instantiate Joystick Left Buttons

	//Instantiate Joystick Right Buttons

	//Instantiate Joystick Buttons Buttons
	b_extend_scaling_arm = new JoystickButton(joystick_buttons, OI_Ports::EXTEND_SCALING_ARM_BUTTON);
	b_retract_scaling_arm = new JoystickButton(joystick_buttons, OI_Ports::RETRACT_SCALING_ARM_BUTTON);
	b_auto_winch = new JoystickButton(joystick_buttons, OI_Ports::AUTO_WINCH_BUTTON);
	b_shooter_engage = new JoystickButton(joystick_buttons, OI_Ports::SHOOTER_ENGAGE_BUTTON);
	b_shooter_disengage = new JoystickButton(joystick_buttons, OI_Ports::SHOOTER_DISENGAGE_BUTTON);
	b_auto_aim = new JoystickButton(joystick_buttons, OI_Ports::AUTO_AIM_BUTTON);

	s_manual_winch_enable = new JoystickButton(joystick_buttons, OI_Ports::MANUAL_WINCH_ENABLE_SWITCH);
	s_shooter_wheels = new JoystickButton(joystick_buttons, OI_Ports::SHOOTER_WHEELS_SWITCH);
	s_intake_belt_forward = new JoystickButton(joystick_buttons, OI_Ports::INTAKE_BELT_FORWARD_SWITCH);
	s_intake_belt_backward = new JoystickButton(joystick_buttons, OI_Ports::INTAKE_BELT_BACKWARD_SWITCH);

	d_intake_angle = new AnalogTrigger(intake_angle);
	d_shooter_speed = new AnalogTrigger(shooter_speed);
	d_manual_aim = new AnalogTrigger(manual_aim);

	//TODO:Instantiate front/back winch joysticks

	//Set Joystick Left Events

	//Set Joystick Right Events

	//Set Joystick Buttons Events

	// Process operator interface input here.
}

float OI::getJoystickLeftY()
{
	return joystick_left->GetY();
}

float OI::getJoystickRightY()
{
	return joystick_right->GetY();
}

Intake::IntakeDirection OI::getIntakeDirection()
{
	if (s_intake_belt_forward->Get())
	{
		return Intake::IntakeDirection::INTAKE_IN;
	}
	else if (s_intake_belt_backward->Get())
	{
		return Intake::IntakeDirection::INTAKE_OUT;
	}
	else
	{
		return Intake::IntakeDirection::INTAKE_STILL;
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
