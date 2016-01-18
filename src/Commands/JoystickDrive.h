#ifndef JoystickDrive_H
#define JoystickDrive_H

#include <CommandBase.h>
#include <Subsystems/Mobility.h>
#include <WPILib.h>

class JoystickDrive: public CommandBase
{
public:
	float leftInput;
	float rightInput;
	JoystickDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
};

#endif
