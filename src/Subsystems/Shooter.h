#ifndef Shooter_H
#define Shooter_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter: public Subsystem
{
public:
	static Shooter* getInstance();
	void InitDefaultCommand();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
private:
	Shooter();
	static Shooter* INSTANCE;
};

#endif
