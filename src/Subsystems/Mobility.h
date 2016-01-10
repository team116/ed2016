#ifndef Mobility_H
#define Mobility_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Mobility: public Subsystem
{
public:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	void InitDefaultCommand();

	static Mobility* getInstance();

private:
	Mobility();
	static Mobility* INSTANCE;
};

#endif
