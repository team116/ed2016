#ifndef Climber_H
#define Climber_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Climber: public Subsystem
{
public:
	void InitDefaultCommand();
	static Climber* getInstance();
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

private:
	Climber();
	static Climber* INSTANCE;

};

#endif
