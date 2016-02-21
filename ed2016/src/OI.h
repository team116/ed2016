#ifndef OI_H
#define OI_H

#include <Joystick.h>
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

	void process();

private:
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
	JoystickButton* b_drive_align_left;
	JoystickButton* b_drive_align_right;

	static const float DIAL_UPDATE_TIME;

	int intake_angle_position_process;
	int shooter_speed_position_process;
	int manual_aim_position_process;

	int shooter_speed_position;

	Timer* angle_temmie;
	Timer* speed_temmie;
	Timer* aim_temmie;

	Log* log;
};
#endif
