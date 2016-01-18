#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include <Subsystems/Shooter.h>

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
	Joystick* joystick2;

	JoystickButton* intake_in;
	JoystickButton* intake_out;
	JoystickButton* shoot;
	JoystickButton* aim_shooter_up;
	JoystickButton* aim_shooter_down;
	JoystickButton* extend_arm;
	JoystickButton* retrive_arm;
	JoystickButton* arm_claw_open_close;
};

#endif
