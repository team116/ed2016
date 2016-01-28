#include <Commands/IntakeDefault.h>
#include <CommandBase.h>

IntakeDefault::IntakeDefault(Intake::IntakeDirection new_direction)
{
	//Requires(intake);

	direction = new_direction;
}

void IntakeDefault::Initialize()
{

}

void IntakeDefault::Execute()
{
	intake->setIntakeDirection (direction);
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
