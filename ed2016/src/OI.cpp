#include <cstdlib>
#include <OI.h>
#include <Commands/SelectCamera.h>
#include <Commands/PullFrontClimberWinch.h>
#include <Commands/PushFrontClimberWinch.h>
#include <Commands/PullBackClimberWinch.h>
#include <Commands/PushBackClimberWinch.h>
#include <Commands/LowerClimberArm.h>
#include <Commands/RaiseClimberArm.h>
#include <Commands/AngleIntake.h>
#include <Commands/RaiseIntake.h>
#include <Commands/LowerIntake.h>

OI* OI::INSTANCE = nullptr;

OI::OI()
{
	//Instantiate Additional Analog Inputs
	intake_angle = new AnalogInput(OI_Ports::INTAKE_ANGLE_DIAL);
	shooter_speed = new AnalogInput(OI_Ports::SHOOTER_SPEED_DIAL);
	manual_aim = new AnalogInput(OI_Ports::MANUAL_AIM_DIAL);

	//Instantiate Joysticks
	joystick_left = new Joystick(OI_Ports::LEFT_JOYSTICK);
	joystick_right = new Joystick(OI_Ports::RIGHT_JOYSTICK);
	joystick_buttons = new Joystick(OI_Ports::BUTTONS_JOYSTICK);
	joystick_buttons->GetAxis(Joystick::AxisType::kXAxis);
	joystick_buttons->GetAxis(Joystick::AxisType::kYAxis);

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
	b_extend_scaling_arm->WhileHeld(new PushFrontClimberWinch());
	b_retract_scaling_arm->WhileHeld(new PullFrontClimberWinch());

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

float OI::getBackWinchY()
{
	return joystick_buttons->GetY();
}
float OI::getFrontWinchY()
{
	return joystick_buttons->GetX();
}

OI* OI::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new OI();
	}
	return INSTANCE;
}
