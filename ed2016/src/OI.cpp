<<<<<<< HEAD
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
	b_clear_commands = new JoystickButton(joystick_buttons, OI_Ports::CLEAR_COMMANDS_BUTTON);

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
=======
#include <cstdlib>
#include <OI.h>
#include <Commands/ExtendScalingArm.h>
#include <Commands/RetractWinches.h>
#include <Commands/AutoAim.h>
#include <Commands/ClearCommands.h>
#include <Commands/IntakeIn.h>
#include <Commands/IntakeOut.h>

#include <Commands/RunShooterWheels.h>
#include <Commands/SelectCamera.h>
#include <Commands/Shoot.h>
#include <Commands/WinchControls.h>
#include <Commands/PullFrontClimberWinch.h>
#include <Commands/PushFrontClimberWinch.h>
#include <Commands/PullBackClimberWinch.h>
#include <Commands/PushBackClimberWinch.h>
#include <Commands/LowerClimberArm.h>
#include <Commands/RaiseClimberArm.h>
#include <Commands/AngleIntake.h>
#include <Commands/RaiseIntake.h>
#include <Commands/LowerIntake.h>

OI::OI()
{
	//Instantiate Joysticks
	joystick_left = new Joystick(OI_Ports::LEFT_JOYSTICK);
	joystick_right = new Joystick(OI_Ports::RIGHT_JOYSTICK);
	joystick_buttons1 = new Joystick(OI_Ports::BUTTONS_JOYSTICK1);
	joystick_buttons2 = new Joystick(OI_Ports::BUTTONS_JOYSTICK2);

	//Instantiate Joystick Left Buttons

	//Instantiate Joystick Right Buttons

	//Instantiate Joystick Buttons 1's Buttons
	b_auto_aim = new JoystickButton(joystick_buttons1, OI_Ports::AUTO_AIM_BUTTON);
	b_shooter_disengage = new JoystickButton(joystick_buttons1, OI_Ports::SHOOTER_DISENGAGE_BUTTON);
	b_shooter_engage = new JoystickButton(joystick_buttons1, OI_Ports::SHOOTER_ENGAGE_BUTTON);
	b_clear_commands = new JoystickButton(joystick_buttons1, OI_Ports::CLEAR_COMMANDS_BUTTON);
	s_shooter_wheels = new JoystickButton(joystick_buttons1, OI_Ports::SHOOTER_WHEELS_SWITCH);
	s_intake_belt_inward = new JoystickButton(joystick_buttons1, OI_Ports::INTAKE_BELT_FORWARD_SWITCH);
	s_intake_belt_outward = new JoystickButton(joystick_buttons1, OI_Ports::INTAKE_BELT_BACKWARD_SWITCH);

	// Instantiate Joystick Buttons 2's Buttons
	b_extend_scaling_arm = new JoystickButton(joystick_buttons2, OI_Ports::EXTEND_SCALING_ARM_BUTTON);
	b_retract_scaling_arm = new JoystickButton(joystick_buttons2, OI_Ports::RETRACT_SCALING_ARM_BUTTON);
	b_auto_winch = new JoystickButton(joystick_buttons2, OI_Ports::AUTO_WINCH_BUTTON);
	b_auto_climber_deploy = new JoystickButton(joystick_buttons2, OI_Ports::AUTO_CLIMBER_DEPLOY_BUTTON);
	s_manual_winch_enable = new JoystickButton(joystick_buttons2, OI_Ports::MANUAL_WINCH_ENABLE_SWITCH);

	//Set Joystick Left Events

	//Set Joystick Right Events

	//Set Joystick Buttons Events
	b_extend_scaling_arm->WhenPressed(new IntakeIn());
	b_retract_scaling_arm->WhenPressed(new IntakeOut());
	b_auto_winch->WhenPressed(new RetractWinches());
	b_auto_climber_deploy->WhenPressed(new ExtendScalingArm());
	b_shooter_engage->WhenPressed(new Shoot());
	b_auto_aim->WhenPressed(new AutoAim());
	b_clear_commands->WhenPressed(new ClearCommands());

	//Set Joystick Switch Events
	s_manual_winch_enable->WhileHeld(new WinchControls());
	s_shooter_wheels->WhileHeld(new RunShooterWheels());
	s_intake_belt_inward->WhileHeld(new IntakeIn());
	s_intake_belt_outward->WhileHeld(new IntakeOut());


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

float OI::getFrontWinchY()
{
	return joystick_buttons1->GetRawAxis(OI_Ports::FRONT_WINCH_JOYSTICK);
}

float OI::getBackWinchY()
{
	return joystick_buttons1->GetRawAxis(OI_Ports::BACK_WINCH_JOYSTICK);
}

int OI::getShooterSpeedPosition()
{
	// assumes GetRawAxis returns in the range [0.0, 1.0]
	return Utils::voltageConversion(joystick_buttons1->GetRawAxis(OI_Ports::SHOOTER_SPEED_DIAL), 6, 1.0);
}
>>>>>>> d699925c2e9ddffb49bbc4f7b60ab2f174851813
