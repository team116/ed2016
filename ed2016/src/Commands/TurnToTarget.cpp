#include "TurnToTarget.h"
#include <Subsystems/Mobility.h>
#include <Subsystems/Cameras.h>

const float P = 0.6;
const float MIN_TURN_SPEED = 0.2;
const float MAX_TURN_SPEED = 0.4;

const float ACCEPTED_ERROR = 5;//in pixels

const float TIMEOUT = 5;//Arbitrary

TurnToTarget::TurnToTarget()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(&*mobility);

	SetTimeout(TIMEOUT);

	pixels_off = 0;
}

// Called just before this Command runs the first time
void TurnToTarget::Initialize()
{
	log->write(Log::TRACE_LEVEL, "TurnToTarget initialized");

	pixels_off = 0;
}

// Called repeatedly when this Command is scheduled to run
void TurnToTarget::Execute()
{
	cameras->RefreshContours();
	if (cameras->canSeeGoal())
	{
		pixels_off = cameras->HorizontalPixelsFromTarget();
		DriverStation::ReportError(std::to_string(pixels_off));
		float offset = fabs(pixels_off / (cameras->IMAGE_WIDTH / 2));

		if (pixels_off < -ACCEPTED_ERROR)
		{
			//DriverStation::ReportError("Turning Left " + std::to_string(pixels_off));
			mobility->setLeft(-1 * Utils::boundaryCheck((P * offset), MIN_TURN_SPEED, MAX_TURN_SPEED));
			mobility->setRight(Utils::boundaryCheck((P * offset), MIN_TURN_SPEED, MAX_TURN_SPEED));
		}
		else if (pixels_off > ACCEPTED_ERROR)
		{
			//DriverStation::ReportError("Turning Right" + std::to_string(pixels_off));
			mobility->setLeft(Utils::boundaryCheck((P * offset), MIN_TURN_SPEED, MAX_TURN_SPEED));
			mobility->setRight(-1 * Utils::boundaryCheck((P * offset), MIN_TURN_SPEED, MAX_TURN_SPEED));
		}
		else
		{
			//DriverStation::ReportError("Lined Up" + std::to_string(pixels_off));
			mobility->setLeft(0.0);
			mobility->setRight(0.0);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool TurnToTarget::IsFinished()
{
	if(fabs(pixels_off) <= ACCEPTED_ERROR)
	{
		return true;
	}
	else if(IsTimedOut())
	{
		log->write(Log::WARNING_LEVEL, "TurnToTarget timed out (Time: %f Pixels Off: %f)", TIMEOUT, pixels_off);
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void TurnToTarget::End()
{
	log->write(Log::TRACE_LEVEL, "TurnToTarget ended (Pixels Off: %f)", pixels_off);
	mobility->setStraight(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnToTarget::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "TurnToTarget interrupted (Pixels Off: %f)", pixels_off);
	End();
}
