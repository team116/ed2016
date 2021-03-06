#ifndef JoystickDrive_H
#define JoystickDrive_H

#include <CommandBase.h>
#include <Subsystems/Mobility.h>
#include <WPILib.h>

class JoystickDrive: public CommandBase
{
public:
	JoystickDrive();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	float leftInput;
	float rightInput;
};

#endif
