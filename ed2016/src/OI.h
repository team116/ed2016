#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include <Subsystems/Shooter.h>
#include <Joystick.h>

class OI
{
public:
	static OI* getInstance();
	float getJoystickLeftY();
	float getJoystickRightY();

	Shooter::IntakeDirection getIntakeDirection();

private:
	OI();
	static OI* INSTANCE;
	Joystick* joystick_left;
	Joystick* joystick_right;
	Joystick* joystick_buttons;

	//Joystick 0 Buttons

	//Joystick 1 Buttons

	//Joystick 2 Buttons
	JoystickButton* intake_in;
	JoystickButton* intake_out;
	JoystickButton* shoot;
	JoystickButton* aim_shooter_up;
	JoystickButton* aim_shooter_down;
	JoystickButton* extend_arm;
	JoystickButton* retrive_arm;
	JoystickButton* arm_claw_open_close;
	JoystickButton* select_camera_front;
	JoystickButton* select_camera_back;
};

#endif
