#include "ManualWinchControl.h"

ManualWinchControl::ManualWinchControl()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);

	Requires(&*climber);

	back_winch = 0.0;
	front_winch = 0.0;
}

// Called just before this Command runs the first time
void ManualWinchControl::Initialize()
{
	back_winch = 0.0;
	front_winch = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void ManualWinchControl::Execute()
{
	back_winch = oi->getBackWinchY();
	front_winch = oi->getFrontWinchY();

	climber->setFrontWinchSpeed(front_winch);
	climber->setBackWinchSpeed(back_winch);
}

// Make this return true when this Command no longer needs to run execute()
bool ManualWinchControl::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ManualWinchControl::End()
{
	climber->setFrontWinchDirection(Climber::WinchDirection::ROBOT_STILL);
	climber->setBackWinchDirection(Climber::WinchDirection::ROBOT_STILL);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualWinchControl::Interrupted()
{
	End();
}
