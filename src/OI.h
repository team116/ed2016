#ifndef OI_H
#define OI_H

#include <WPILib.h>
#include <Joystick.h>

class OI
{
public:
	static OI* getInstance();

private:
	OI();
	static OI* INSTANCE;

	Joystick* joystick0;
};

#endif
