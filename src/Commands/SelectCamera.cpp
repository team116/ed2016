#include "SelectCamera.h"

SelectCamera::SelectCamera(int cam)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(cameras);

	camera = cam;
}

// Called just before this Command runs the first time
void SelectCamera::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void SelectCamera::Execute()
{
	if(cameras->StopCamera(camera == 1 ? 0 : 1))
	{
		cameras->StartCamera(camera);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool SelectCamera::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void SelectCamera::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SelectCamera::Interrupted()
{

}
