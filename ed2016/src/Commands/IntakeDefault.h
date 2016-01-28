#ifndef SRC_COMMANDS_INTAKEDEFAULT_H_
#define SRC_COMMANDS_INTAKEDEFAULT_H_
#include <CommandBase.h>
#include <Subsystems/Shooter.h>
#include <WPILib.h>

class IntakeDefault : public CommandBase
{
public:
	IntakeDefault(Intake::IntakeDirection new_direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:

	Intake::IntakeDirection direction;

};

#endif
