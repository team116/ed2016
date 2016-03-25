#include <Commands/MoveIntake.h>
#include <CommandBase.h>
#include <Subsystems/HolderWheel.h>
#include <Subsystems/IntakeRoller.h>
#include <Subsystems/Sensors.h>


MoveIntake::MoveIntake(Utils::HorizontalDirection direction)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*intake_roller);
	Requires(&*holder_wheel);

	 this->direction = direction;
}

// Called just before this Command runs the first time
void MoveIntake::Initialize()
{
	log->write(Log::TRACE_LEVEL, "MoveIntake Initialized");
	intake_roller->setDirection(direction);
	holder_wheel->setWheelDirection(direction);
}

// Called repeatedly when this Command is scheduled to run
void MoveIntake::Execute()
{
	if (direction == Utils::HorizontalDirection::IN)
	{
		if (sensors->readyToShoot())
		{
			holder_wheel->setWheelDirection(Utils::HorizontalDirection::H_STILL);
		}
		else
		{
			holder_wheel->setWheelDirection(direction);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool MoveIntake::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveIntake::End()
{
	log->write(Log::TRACE_LEVEL, "MoveIntake Ended");
	CommandBase::intake_roller->setDirection(Utils::HorizontalDirection::H_STILL);
	CommandBase::holder_wheel->setWheelDirection(Utils::HorizontalDirection::H_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveIntake::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "MoveIntake Interrupted");
	End();
}
