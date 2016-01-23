#include <Commands/IntakeDefault.h>
#include <CommandBase.h>

IntakeDefault::IntakeDefault(Shooter::IntakeDirection new_direction)
{
	Requires(shooter);

	direction = new_direction;
}

void IntakeDefault::Initialize()
{

}

void IntakeDefault::Execute()
{
	shooter->setIntakeDirection (direction);
}

bool IntakeDefault::IsFinished()
{
	return false;
}

void IntakeDefault::End()
{

}

void IntakeDefault::Interrupted()
{

}
