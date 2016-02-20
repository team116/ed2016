#ifndef ShooterPID_H
#define ShooterPID_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"

class ShooterPID: public PIDSubsystem
{
public:
	ShooterPID();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
};

#endif
