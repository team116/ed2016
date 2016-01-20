#ifndef SRC_COMMANDS_INTAKEDEFAULT_H_
#define SRC_COMMANDS_INTAKEDEFAULT_H_
#include <commandbase.h>
#include <Subsystems/Shooter.h>
#include <WPILib.h>

class IntakeDefault : public CommandBase
{
public:
	IntakeDefault(Shooter::IntakeDirection new_direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:

	Shooter::IntakeDirection direction;

};

#endif
