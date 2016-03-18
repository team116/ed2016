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
#include <Commands/MoveHolderWheel.h>
#include <Commands/AngleIntake.h>
#include <Commands/MoveIntake.h>
#include <Commands/DriveStraight.h>
#include <Commands/DriveDistance.h>
#include <Commands/JoystickTurn.h>
#include <Commands/TogglePID.h>
#include <Subsystems/Intake.h>
#include <Subsystems/ShooterPID.h>
#include <Subsystems/ShooterPitch.h>

const float OI::DRIVE_JOYSTICK_SCALE = 0.5;
const float OI::DIAL_UPDATE_TIME = 0.05;
const float OI::DEAD_ZONE_AMOUNT = 0.1;

// stupid stuff has to be static.  wah
SetShooterPitch** OI::set_shooter_pitch = new SetShooterPitch*[ShooterPitch::ANGLE_PRESET_COUNT];
AngleIntake** OI::angle_intake = new AngleIntake*[Intake::ANGLE_PRESET_COUNT];

OI::OI()
{
	//Instantiate Joysticks
	joystick_left = new Joystick(OI_Ports::LEFT_JOYSTICK);
	joystick_right = new Joystick(OI_Ports::RIGHT_JOYSTICK);
	joystick_buttons1 = new Joystick(OI_Ports::BUTTONS_JOYSTICK1);
	joystick_buttons2 = new Joystick(OI_Ports::BUTTONS_JOYSTICK2);

	//Instantiate Joystick Right Buttons
	b_drive_align_right = new JoystickButton(joystick_right, OI_Ports::B_DRVIE_ALIGN_BUTTON_RIGHT);
	b_turn_x_axis_right = new JoystickButton(joystick_right, OI_Ports::B_TURN_X_AXIS_RIGHT);


	//Instantiate Joystick Left Buttons
	b_drive_align_left = new JoystickButton(joystick_left, OI_Ports::B_DRIVE_ALIGN_BUTTON_LEFT);
	b_turn_x_axis_left = new JoystickButton(joystick_left, OI_Ports::B_TURN_X_AXIS_LEFT);

	//Instantiate Joystick Buttons 1's Buttons
	b_test_button = new JoystickButton(joystick_buttons1, OI_Ports::TEST_BUTTON);
	b_auto_aim = new JoystickButton(joystick_buttons1, OI_Ports::AUTO_AIM_BUTTON);
	b_shooter_engage = new JoystickButton(joystick_buttons1, OI_Ports::SHOOT_BUTTON);
	b_clear_commands = new JoystickButton(joystick_buttons1, OI_Ports::CLEAR_COMMANDS_BUTTON);
	s_shooter_wheels = new JoystickButton(joystick_buttons1, OI_Ports::SHOOTER_WHEELS_SWITCH);
	s_intake_belt_inward = new JoystickButton(joystick_buttons1, OI_Ports::INTAKE_BELT_FORWARD_SWITCH);
	s_intake_belt_outward = new JoystickButton(joystick_buttons1, OI_Ports::INTAKE_BELT_BACKWARD_SWITCH);
	s_pid_enable = new JoystickButton(joystick_buttons1, OI_Ports::PID_TOGGLE_SWITCH);

	// Instantiate Joystick Buttons 2's Buttons
	b_extend_scaling_arm = new JoystickButton(joystick_buttons2, OI_Ports::EXTEND_SCALING_ARM_BUTTON);
	b_retract_scaling_arm = new JoystickButton(joystick_buttons2, OI_Ports::RETRACT_SCALING_ARM_BUTTON);
	b_auto_winch = new JoystickButton(joystick_buttons2, OI_Ports::AUTO_WINCH_BUTTON);
	b_auto_climber_deploy = new JoystickButton(joystick_buttons2, OI_Ports::AUTO_CLIMBER_DEPLOY_BUTTON);
	s_manual_winch_enable = new JoystickButton(joystick_buttons2, OI_Ports::MANUAL_WINCH_ENABLE_SWITCH);

	//Set Joystick Left Events
	b_drive_align_left->WhileHeld(new DriveStraight(DriveStraight::LEFT, DriveStraight::GYRO));
	b_turn_x_axis_left->WhileHeld(new JoystickTurn(JoystickTurn::LEFT));

	//Set Joystick Right Events
	b_drive_align_right->WhileHeld(new DriveStraight(DriveStraight::RIGHT, DriveStraight::GYRO));
	b_turn_x_axis_right->WhileHeld(new JoystickTurn(JoystickTurn::RIGHT));


	//Set Joystick Buttons Events

	b_extend_scaling_arm->WhileHeld(new MoveClimberArm(Utils::VerticalDirection::UP));
	b_retract_scaling_arm->WhileHeld(new MoveClimberArm(Utils::VerticalDirection::DOWN));
	b_auto_winch->WhenPressed(new RetractWinches());
	b_auto_climber_deploy->WhenPressed(new ExtendScalingArm());
	b_shooter_engage->WhenPressed(new Shoot());
	b_auto_aim->WhileHeld(new AutoAim());
	//b_clear_commands->WhenPressed(new ClearCommands());
	//b_test_button->ToggleWhenPressed(new DriveStraight(0.5, DriveStraight::SensorType::GYRO));

	//Set Joystick Switch Events
	s_manual_winch_enable->WhileHeld(new ManualWinchControl());
	s_pid_enable->WhenPressed(new TogglePID(true));
	s_pid_enable->WhenReleased(new TogglePID(false));
	/*
	s_intake_belt_inward->WhenPressed(new MoveIntake(Utils::HorizontalDirection::IN));
	s_intake_belt_inward->WhenReleased(new MoveIntake(Utils::HorizontalDirection::H_STILL));
	s_intake_belt_outward->WhenPressed(new MoveIntake(Utils::HorizontalDirection::OUT));
	s_intake_belt_outward->WhenReleased(new MoveIntake(Utils::HorizontalDirection::H_STILL));
	*/
	//Set Joystick Analog Dial Events

	//Set any other variables here
	intake_angle_position_process = -1;
	shooter_speed_position_process = -1;
	manual_aim_position_process = -1;
	last_intake_direction = Utils::HorizontalDirection::H_STILL;

	shooter_speed_position = 0;

	for (int i = 0; i < ShooterPitch::ANGLE_PRESET_COUNT; ++i)
	{
		set_shooter_pitch[i] = new SetShooterPitch(ShooterPitch::getAnglePreset(i));
	}
	for (int i = 0; i < Intake::ANGLE_PRESET_COUNT; ++i)
	{
		angle_intake[i] = new AngleIntake(Intake::getAnglePreset(i));
	}

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
	int intake_angle_curr = Utils::voltageConversion(2.0 - (joystick_buttons1->GetRawAxis(OI_Ports::INTAKE_ANGLE_DIAL) + 1.0), 6, 2.0);
	int shooter_speed_curr = Utils::voltageConversion(2.0 - (joystick_buttons1->GetRawAxis(OI_Ports::SHOOTER_SPEED_DIAL) + 1.0), 6, 2.0);
	int manual_aim_curr = Utils::voltageConversion(2.0 - (joystick_buttons1->GetRawAxis(OI_Ports::MANUAL_AIM_DIAL) + 1.0), 6, 2.0);

	//Intake Angle Dial
	if(intake_angle_curr != intake_angle_position_process) {
		angle_temmie->Reset();
		angle_temmie->Start();
		intake_angle_position_process = intake_angle_curr;
	}
	else if(angle_temmie->HasPeriodPassed(DIAL_UPDATE_TIME)) {
		Scheduler::GetInstance()->AddCommand(angle_intake[intake_angle_position_process]);
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
		if (getPIDEnableSwitch())
		{
			CommandBase::shooter_pitch->Enable();
		}
		else
		{
			CommandBase::shooter_pitch->Disable();
		}
		Scheduler::GetInstance()->AddCommand(set_shooter_pitch[manual_aim_position_process]);
		aim_temmie->Reset();
		aim_temmie->Stop();

		if (b_clear_commands->Get())
		{
			DriverStation::ReportError("\nClearing commands.");
			Scheduler::GetInstance()->RemoveAll();
		}
	}
	
	Utils::HorizontalDirection intake_direction = getIntakeDirectionSwitch();
	if (intake_direction != last_intake_direction)
	{
		resetIntakeDirectionSwitch();
	}
	/*
	CommandBase::shooter_pitch_pid->setP(SmartDashboard::GetNumber("p-val", CommandBase::shooter_pitch_pid->getP()));
	CommandBase::shooter_pitch_pid->setI(SmartDashboard::GetNumber("i-val", CommandBase::shooter_pitch_pid->getI()));
	CommandBase::shooter_pitch_pid->setD(SmartDashboard::GetNumber("d-val", CommandBase::shooter_pitch_pid->getD()));
	*/
}

float OI::getJoystickLeftY()
{
	float val = -1.0 * Utils::deadZoneCheck(joystick_left->GetY(), DEAD_ZONE_AMOUNT);
	float curved;

	if(val > 0)
	{
		curved = pow(val, 2);
	}
	else if(val < 0)
	{
		curved = pow(val, 2) * -1;
	}
	else
	{
		return 0.0;
	}
	return curved * DRIVE_JOYSTICK_SCALE;
}

float OI::getJoystickRightY()
{
	float val = -1.0 * Utils::deadZoneCheck(joystick_right->GetY(), DEAD_ZONE_AMOUNT);
	float curved;

	if(val > 0)
	{
		curved = pow(val, 2);
	}
	else if(val < 0)
	{
		curved = pow(val, 2) * -1;
	}
	else
	{
		return 0.0;
	}
	return curved * DRIVE_JOYSTICK_SCALE;
}

float OI::getJoystickLeftZ()
{
	float val = -1.0 * Utils::deadZoneCheck(joystick_left->GetZ(), DEAD_ZONE_AMOUNT);
	if(val > 0) {
		return pow(val, 2);
	}
	if (val < 0) {
		return pow(val, 2) * -1;
	}
	return 0;
}

float OI::getJoystickRightZ()
{
	float val = -1.0 * Utils::deadZoneCheck(joystick_right->GetZ(), DEAD_ZONE_AMOUNT);
	if (val > 0) {
		return pow(val,2);
	}
	if (val < 0) {
		return pow(val, 2) * -1;
	}
	return 0;
}

float OI::getFrontWinchY()
{
	return pow(Utils::deadZoneCheck(joystick_buttons2->GetRawAxis(OI_Ports::FRONT_WINCH_JOYSTICK), DEAD_ZONE_AMOUNT), 3);
}

float OI::getBackWinchY()
{
	return pow(Utils::deadZoneCheck(joystick_buttons2->GetRawAxis(OI_Ports::BACK_WINCH_JOYSTICK), DEAD_ZONE_AMOUNT), 3);
}

int OI::getShooterSpeedPosition()
{
	return shooter_speed_position;
}

bool OI::getShooterWheelsSwitch()
{
	return s_shooter_wheels->Get();
}

Utils::HorizontalDirection OI::getIntakeDirectionSwitch()
{
	if (s_intake_belt_inward->Get())
	{
		return Utils::HorizontalDirection::IN;
	}
	else if (s_intake_belt_outward->Get())
	{
		return Utils::HorizontalDirection::OUT;
	}
	return Utils::HorizontalDirection::H_STILL;
}

void OI::resetIntakeDirectionSwitch()
{
	Utils::HorizontalDirection intake_direction = getIntakeDirectionSwitch();
	Scheduler::GetInstance()->AddCommand(new MoveIntake(intake_direction));
	last_intake_direction = intake_direction;
}

bool OI::getPIDEnableSwitch()
{
	return s_pid_enable->Get();
}
