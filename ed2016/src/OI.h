#ifndef OI_H
#define OI_H

#include <Joystick.h>
#include <Commands/AngleIntake.h>
#include <Commands/AutoShoot.h>
#include <Commands/ControlShooterPitch.h>
#include <Commands/MoveIntake.h>
#include <Commands/MoveShooter.h>
#include <Commands/SetShooterPitch.h>
#include <Commands/Shoot.h>
#include <Subsystems/Intake.h>
#include <WPILib.h>
#include <Log.h>

class OI
{
public:
	OI();

	float getJoystickLeftY();
	float getJoystickRightY();

	float getJoystickRightZ();
	float getJoystickLeftZ();

	float getBackWinchY();
	float getFrontWinchY();

	int getShooterSpeedPosition();

	bool getShooterWheelsSwitch();

	bool getFuegoButton();
	bool getAutoAimButton();
	bool getSensorEnableSwitch();

	Utils::HorizontalDirection getIntakeDirectionSwitch();
	void resetIntakeDirectionSwitch();

	void process();

	bool getPIDEnableSwitch();

	void updateAngle();

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
//	JoystickButton* b_test_button;
//	JoystickButton* b_clear_commands;
	JoystickButton* b_move_intake_up;
	JoystickButton* b_move_intake_down;

	JoystickButton* s_manual_winch_enable;
	JoystickButton* s_shooter_wheels;
	JoystickButton* s_intake_belt_inward;
	JoystickButton* s_intake_belt_outward;
	JoystickButton* s_pid_enable;
	JoystickButton* s_sensor_override;

	JoystickButton* b_drive_align_left;
	JoystickButton* b_drive_align_right;

	JoystickButton* b_turn_x_axis_right;
	JoystickButton* b_turn_x_axis_left;

	static const float DIAL_UPDATE_TIME;
	static const float DEAD_ZONE_AMOUNT;

	int intake_angle_position_process;
	int shooter_speed_position_process;
	int manual_aim_position_process;
	Utils::HorizontalDirection last_intake_direction;

	int shooter_speed_position;

	// commands
	AngleIntake** angle_intake;
	ControlShooterPitch* control_shooter_pitch;
	MoveIntake* move_intake_in;
	MoveIntake* move_intake_still;
	MoveIntake* move_intake_out;
	SetShooterPitch** set_shooter_pitch;

	Timer* angle_temmie;
	Timer* speed_temmie;
	Timer* aim_temmie;

	Log* log;
};
#endif
