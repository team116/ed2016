#ifndef OI_H
#define OI_H

#include <Joystick.h>
#include <Commands/AngleIntake.h>
#include <Commands/SetShooterPitch.h>
#include <Subsystems/Intake.h>
#include <WPILib.h>
#include <Log.h>

class OI
{
public:
	OI();

	float getJoystickLeftY();
	float getJoystickRightY();

	float getBackWinchY();
	float getFrontWinchY();

	int getShooterSpeedPosition();

	bool getShooterWheelsSwitch();

	Utils::HorizontalDirection getIntakeDirectionSwitch();
	void resetIntakeDirectionSwitch();

	void process();

	bool getPIDEnableSwitch();

private:
	static const float DRIVE_JOYSTICK_SCALE;
	Joystick* joystick_left;
	Joystick* joystick_right;
	Joystick* joystick_buttons1;
	Joystick* joystick_buttons2;

	/*
	 * Prefix Key:
	 * b = button
	 * s = switch
	 * d = dial
	 * j = joystick
	 */

	//Joystick 0 Buttons

	//Joystick 1 Buttons

	//Joystick 2 Buttons
	JoystickButton* b_extend_scaling_arm;
	JoystickButton* b_retract_scaling_arm;
	JoystickButton* b_auto_winch;
	JoystickButton* b_auto_climber_deploy;
	JoystickButton* b_shooter_engage;
	JoystickButton* b_auto_aim;
	JoystickButton* b_clear_commands;

	JoystickButton* s_manual_winch_enable;
	JoystickButton* s_shooter_wheels;
	JoystickButton* s_intake_belt_inward;
	JoystickButton* s_intake_belt_outward;
	JoystickButton* s_pid_enable;

	JoystickButton* b_drive_align_left;
	JoystickButton* b_drive_align_right;

	JoystickButton* b_test_button;

	static const float DIAL_UPDATE_TIME;
	static const float DEAD_ZONE_AMOUNT;

	int intake_angle_position_process;
	int shooter_speed_position_process;
	int manual_aim_position_process;
	Utils::HorizontalDirection last_intake_direction;

	int shooter_speed_position;

	static SetShooterPitch** set_shooter_pitch;
	static AngleIntake** angle_intake;

	Timer* angle_temmie;
	Timer* speed_temmie;
	Timer* aim_temmie;

	Log* log;
};
#endif
