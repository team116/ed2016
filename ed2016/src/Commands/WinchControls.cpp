#include "WinchControls.h"
#include "OI.h"
WinchControls::WinchControls()
{
	// Use Requires(&*) here to declare subsystem dependencies
	// eg. Requires(&*chassis);
	back_winch = 0.0;
	front_winch = 0.0;

}

// Called just before this Command runs the first time
void WinchControls::Initialize()
{
	back_winch = 0.0;
	front_winch = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void WinchControls::Execute()
{
	back_winch = oi->getBackWinchY();
	front_winch = oi->getFrontWinchY();

}

// Make this return true when this Command no longer needs to run execute()
bool WinchControls::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void WinchControls::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WinchControls::Interrupted()
{

}
