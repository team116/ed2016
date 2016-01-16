#include <cstdlib>
#include <OI.h>
#include <Commands/SelectCamera.h>

OI* OI::INSTANCE = nullptr;

OI::OI()
{
	// Process operator interface input here.

	joystick0 = new Joystick(0);

	JoystickButton* button1 = new JoystickButton(joystick0, 1);
	JoystickButton* button2 = new JoystickButton(joystick0, 2);

	button1->WhenPressed(new SelectCamera(0));
	button2->WhenPressed(new SelectCamera(1));

	DriverStation::ReportError("Running OI");
}

OI* OI::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new OI();
	}
	return INSTANCE;
}
