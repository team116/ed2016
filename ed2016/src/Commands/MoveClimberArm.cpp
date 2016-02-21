#include <Commands/MoveClimberArm.h>
#include <CommandBase.h>
#include <Subsystems/Climber.h>

MoveClimberArm::MoveClimberArm(Climber::ClimberArmDirection direction, float speed)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*climber);

	this->direction = direction;
	this->speed = speed;
}

// Called just before this Command runs the first time
void MoveClimberArm::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void MoveClimberArm::Execute()
{
	CommandBase::climber->setClimber(direction);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveClimberArm::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveClimberArm::End()
{
	CommandBase::climber->setClimber(Climber::CLIMBER_ARM_STILL, speed);	//add loat speed
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveClimberArm::Interrupted()
{

}
