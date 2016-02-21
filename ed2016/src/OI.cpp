#include <cstdlib>
#include <OI.h>
#include <Commands/ExtendScalingArm.h>
#include <Commands/RetractWinches.h>
#include <Commands/AutoAim.h>
#include <Commands/ClearCommands.h>
#include <Commands/SetShooterPitch.h>
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
#include <Subsystems/Intake.h>
#include <Commands/MoveIntake.h>
#include <Commands/DriveStraight.h>
#include <Commands/MoveIntake.h>

const float OI::DIAL_TOLERANCE = 0.2;

const float OI::DIAL_1 = 1.0;
const float OI::DIAL_2 = 0.6;
const float OI::DIAL_3 = 0.2;
const float OI::DIAL_4 = -0.2;
const float OI::DIAL_5 = -0.6;
const float OI::DIAL_6 = -1.0;

OI::OI()
{
	//Instantiate Joysticks
	joystick_left = new Joystick(OI_Ports::LEFT_JOYSTICK);
	joystick_right = new Joystick(OI_Ports::RIGHT_JOYSTICK);
	joystick_buttons1 = new Joystick(OI_Ports::BUTTONS_JOYSTICK1);
	joystick_buttons2 = new Joystick(OI_Ports::BUTTONS_JOYSTICK2);

	//Instantiate Joystick Left Buttons
	b_drive_align_left = new JoystickButton(joystick_left, OI_Ports::B_DRIVE_ALIGN_BUTTON_LEFT);

	//Instantiate Joystick Right Buttons
	b_drive_align_right = new JoystickButton(joystick_right, OI_Ports::B_DRVIE_ALIGN_BUTTON_RIGHT);

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
	b_drive_align_left->WhileHeld(new DriveStraight(DriveStraight::LEFT, DriveStraight::GYRO));

	//Set Joystick Right Events
	b_drive_align_right->WhileHeld(new DriveStraight(DriveStraight::RIGHT, DriveStraight::GYRO));

	//Set Joystick Buttons Events
	b_extend_scaling_arm->WhenPressed(new RaiseClimberArm());
	b_retract_scaling_arm->WhenPressed(new LowerClimberArm());
	b_auto_winch->WhenPressed(new RetractWinches());
	b_auto_climber_deploy->WhenPressed(new ExtendScalingArm());
	b_shooter_engage->WhenPressed(new Shoot());
	b_auto_aim->WhenPressed(new AutoAim());
	b_clear_commands->WhenPressed(new ClearCommands());

	//Set Joystick Switch Events
	s_manual_winch_enable->WhileHeld(new WinchControls());
	s_shooter_wheels->WhileHeld(new RunShooterWheels(0.75));
	s_intake_belt_inward->WhileHeld(new MoveIntake(Intake::INTAKE_IN));
	s_intake_belt_outward->WhileHeld(new MoveIntake(Intake::INTAKE_OUT));

	//Set Joystick Analog Dial Events

	// Process operator interface input here.
}

void OI::process()
{
	int manual_aim = Utils::voltageConversion(joystick_buttons1->GetRawAxis(OI_Ports::MANUAL_AIM_DIAL) + 1.0, 6, 2.0);

	switch(manual_aim) {
		case 0:
			Scheduler::GetInstance()->AddCommand(new SetShooterPitch(0, 1));
			break;
		case 1:
			Scheduler::GetInstance()->AddCommand(new SetShooterPitch(15, 1));
			break;
		case 2:
			Scheduler::GetInstance()->AddCommand(new SetShooterPitch(30, 1));
			break;
		case 3:
			Scheduler::GetInstance()->AddCommand(new SetShooterPitch(45, 1));
			break;
		case 4:
			Scheduler::GetInstance()->AddCommand(new SetShooterPitch(60, 1));
			break;
		case 5:
			Scheduler::GetInstance()->AddCommand(new SetShooterPitch(75, 1));
			break;
		default:
			DriverStation::ReportWarning("Manual Aim Dial invalid position: " +
					std::to_string(Utils::voltageConversion(joystick_buttons1->GetRawAxis(OI_Ports::MANUAL_AIM_DIAL) + 1.0, 6, 2.0)) + "\n");
			break;
	}

	/*switch(GetDialPosition(joystick_buttons1->GetRawAxis(OI_Ports::SHOOTER_SPEED_DIAL))) {
		case 1:
			Scheduler::GetInstance()->AddCommand(new RunShooterWheels(0));
			break;
		case 2:
			Scheduler::GetInstance()->AddCommand(new RunShooterWheels(0.2));
			break;
		case 3:
			Scheduler::GetInstance()->AddCommand(new RunShooterWheels(0.4));
			break;
		case 4:
			Scheduler::GetInstance()->AddCommand(new RunShooterWheels(0.6));
			break;
		case 5:
			Scheduler::GetInstance()->AddCommand(new RunShooterWheels(0.8));
			break;
		case 6:
			Scheduler::GetInstance()->AddCommand(new RunShooterWheels(1.0));
			break;
	}

	switch(GetDialPosition(joystick_buttons1->GetRawAxis(OI_Ports::INTAKE_ANGLE_DIAL))) {
		case 1:
			Scheduler::GetInstance()->AddCommand(new AngleIntake(0, 1));
			break;
		case 2:
			Scheduler::GetInstance()->AddCommand(new AngleIntake(18, 1));
			break;
		case 3:
			Scheduler::GetInstance()->AddCommand(new AngleIntake(36, 1));
			break;
		case 4:
			Scheduler::GetInstance()->AddCommand(new AngleIntake(54, 1));
			break;
		case 5:
			Scheduler::GetInstance()->AddCommand(new AngleIntake(72, 1));
			break;
		case 6:
			Scheduler::GetInstance()->AddCommand(new AngleIntake(90, 1));
			break;
	}*/
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
