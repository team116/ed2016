#ifndef OI_H
#define OI_H

#include <Joystick.h>
#include <Subsystems/Intake.h>
#include <WPILib.h>

class OI
{
public:
	static OI* getInstance();

	float getJoystickLeftY();
	float getJoystickRightY();

	float getBackWinchY();
	float getFrontWinchY();

	int getShooterSpeedPosition();

private:
	OI();
	static OI* INSTANCE;
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
	JoystickButton* b_shooter_engage;
	//JoystickButton* b_shooter_disengage;
	JoystickButton* b_auto_aim;
	JoystickButton* b_clear_commands;

	JoystickButton* s_manual_winch_enable;
	JoystickButton* s_shooter_wheels;
	JoystickButton* s_intake_belt_inward;
	JoystickButton* s_intake_belt_outward;

	AnalogTrigger* d_intake_angle;
	AnalogTrigger* d_shooter_speed;
	AnalogTrigger* d_manual_aim;

	//Analog Inputs
	AnalogInput* intake_angle;
	AnalogInput* manual_aim;
};
#endif
