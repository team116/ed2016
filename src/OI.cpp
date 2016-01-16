#include <cstdlib>
#include <OI.h>

OI* OI::INSTANCE = nullptr;

OI::OI()
{
	// Process operator interface input here.

	joystick0 = new Joystick(1);

	JoystickButton* button1 = new JoystickButton(joystick0, 1);
	JoystickButton* button2 = new JoystickButton(joystick0, 2);
}

OI* OI::getInstance()
{
	if (INSTANCE != nullptr)
	{
		INSTANCE = new OI();
	}
	return INSTANCE;
}
