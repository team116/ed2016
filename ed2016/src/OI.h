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

	Intake::IntakeDirection getIntakeDirection();

private:
	OI();
	static OI* INSTANCE;
	Joystick* joystick_left;
	Joystick* joystick_right;
	Joystick* joystick_buttons;

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
	JoystickButton* b_shooter_disengage;
	JoystickButton* b_auto_aim;

	JoystickButton* s_manual_winch_enable;
	JoystickButton* s_shooter_wheels;
	JoystickButton* s_intake_belt_forward;
	JoystickButton* s_intake_belt_backward;

	AnalogTrigger* d_intake_angle;
	AnalogTrigger* d_shooter_speed;
	AnalogTrigger* d_manual_aim;

	AnalogInput* j_manual_front_winch;
	AnalogInput* j_manual_back_winch;

	//Analog Inputs
	AnalogInput* intake_angle;
	AnalogInput* shooter_speed;
	AnalogInput* manual_aim;
	AnalogInput* manual_front_winch;
	AnalogInput* manual_back_winch;
};
#endif
