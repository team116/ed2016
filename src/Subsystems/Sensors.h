#ifndef Sensors_H
#define Sensors_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Sensors: public Subsystem
{
public:
	void InitDefaultCommand();
	static Sensors* getInstance();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:
	Sensors();
	static Sensors* INSTANCE;

};

#endif
