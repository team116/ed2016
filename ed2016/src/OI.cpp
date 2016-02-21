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
#include <Commands/ManualWinchControl.h>
#include <Commands/MoveClimberArm.h>
#include <Commands/AngleIntake.h>
#include <Commands/MoveIntakeAngle.h>
#include <Subsystems/Intake.h>
#include <Commands/MoveIntake.h>
#include <Commands/DriveStraight.h>
#include <Commands/MoveIntake.h>

const float OI::DIAL_UPDATE_TIME = 0.05;
const float OI::DEAD_ZONE_AMOUNT = 0.1;

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
	b_shooter_engage = new JoystickButton(joystick_buttons1, OI_Ports::SHOOT_BUTTON);
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
	b_extend_scaling_arm->WhileHeld(new MoveClimberArm(Utils::VerticalDirection::UP));
	b_retract_scaling_arm->WhileHeld(new MoveClimberArm(Utils::VerticalDirection::DOWN));
	b_auto_winch->WhenPressed(new RetractWinches());
	b_auto_climber_deploy->WhenPressed(new ExtendScalingArm());
	b_shooter_engage->WhenPressed(new Shoot());
	b_auto_aim->WhenPressed(new AutoAim());
	b_clear_commands->WhenPressed(new ClearCommands());

	//Set Joystick Switch Events
	s_manual_winch_enable->WhileHeld(new ManualWinchControl());
	//s_shooter_wheels->WhileHeld(new RunShooterWheels());
	s_intake_belt_inward->WhileHeld(new MoveIntake(Utils::HorizontalDirection::IN));
	s_intake_belt_outward->WhileHeld(new MoveIntake(Utils::HorizontalDirection::OUT));

	//Set Joystick Analog Dial Events

	//Set any other variables here
	intake_angle_position_process = -1;
	shooter_speed_position_process = -1;
	manual_aim_position_process = -1;

	shooter_speed_position = 0;

	angle_temmie = new Timer();
	speed_temmie = new Timer();
	aim_temmie = new Timer();

	angle_temmie->Start();
	speed_temmie->Start();
	aim_temmie->Start();

	log = Log::getInstance();
}

void OI::process()
{
	int intake_angle_curr = Utils::voltageConversion(joystick_buttons1->GetRawAxis(OI_Ports::INTAKE_ANGLE_DIAL) + 1.0, 6, 2.0);
	int shooter_speed_curr = Utils::voltageConversion(joystick_buttons1->GetRawAxis(OI_Ports::SHOOTER_SPEED_DIAL) + 1.0, 6, 2.0);
	int manual_aim_curr = Utils::voltageConversion(joystick_buttons1->GetRawAxis(OI_Ports::MANUAL_AIM_DIAL) + 1.0, 6, 2.0);

	//Intake Angle Dial
	if(intake_angle_curr != intake_angle_position_process) {
		angle_temmie->Reset();
		angle_temmie->Start();
		intake_angle_position_process = intake_angle_curr;
	}
	else if(angle_temmie->HasPeriodPassed(DIAL_UPDATE_TIME)) {
		switch(intake_angle_position_process) {
				case 0:
					Scheduler::GetInstance()->AddCommand(new AngleIntake(0, 1));
					break;
				case 1:
					Scheduler::GetInstance()->AddCommand(new AngleIntake(18, 1));
					break;
				case 2:
					Scheduler::GetInstance()->AddCommand(new AngleIntake(36, 1));
					break;
				case 3:
					Scheduler::GetInstance()->AddCommand(new AngleIntake(54, 1));
					break;
				case 4:
					Scheduler::GetInstance()->AddCommand(new AngleIntake(72, 1));
					break;
				case 5:
					Scheduler::GetInstance()->AddCommand(new AngleIntake(90, 1));
					break;
				default:
					log->write(Log::WARNING_LEVEL, "Intake angle dial invalid position: %d",  intake_angle_position_process);
					break;
			}
		angle_temmie->Reset();
		angle_temmie->Stop();
	}

	//Shooter Speed Dial
	if(shooter_speed_curr != shooter_speed_position_process) {
		speed_temmie->Reset();
		speed_temmie->Start();
		shooter_speed_position_process = shooter_speed_curr;
	}
	else if(speed_temmie->HasPeriodPassed(DIAL_UPDATE_TIME)) {
		shooter_speed_position = shooter_speed_position_process;
		speed_temmie->Reset();
		speed_temmie->Stop();
	}

	//Shooter Pitch Dial
	if(manual_aim_curr != manual_aim_position_process) {
		aim_temmie->Reset();
		aim_temmie->Start();
		manual_aim_position_process = manual_aim_curr;
	}
	else if(aim_temmie->HasPeriodPassed(DIAL_UPDATE_TIME)) {
		switch(manual_aim_position_process) {
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
				log->write(Log::WARNING_LEVEL, "Manual aim dial invalid position: %d", manual_aim_position_process);
				break;
		}
		aim_temmie->Reset();
		aim_temmie->Stop();
	}
}

float OI::getJoystickLeftY()
{
	return pow(Utils::deadZoneCheck(joystick_left->GetY(), DEAD_ZONE_AMOUNT), 3);

}

float OI::getJoystickRightY()
{
	return pow(Utils::deadZoneCheck(joystick_right->GetY(), DEAD_ZONE_AMOUNT), 3);
}

float OI::getFrontWinchY()
{
	return joystick_buttons2->GetRawAxis(OI_Ports::FRONT_WINCH_JOYSTICK);
}

float OI::getBackWinchY()
{
	return joystick_buttons2->GetRawAxis(OI_Ports::BACK_WINCH_JOYSTICK);
}

int OI::getShooterSpeedPosition()
{
	return shooter_speed_position;
}

bool OI::getShooterWheelsSwitch()
{
	return s_shooter_wheels->Get();
}
