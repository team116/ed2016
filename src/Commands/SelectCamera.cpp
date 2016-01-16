#include "SelectCamera.h"

SelectCamera::SelectCamera(int cam)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(cameras);

	camera = cam;

	isFinished = false;
}

// Called just before this Command runs the first time
void SelectCamera::Initialize()
{
	DriverStation::ReportError("Init SelectCamera");

	DriverStation::ReportError("Stopping Camera: " + std::to_string(camera == 1 ? 0 : 1));
	if(cameras->StopCamera(camera == 1 ? 0 : 1))
	{
		DriverStation::ReportError("Starting Camera: " + std::to_string(camera));
		cameras->StartCamera(camera);
	}
}

// Called repeatedly when this Command is scheduled to run
void SelectCamera::Execute()
{
	DriverStation::ReportError("Executing SelectCamera");
	cameras->RunCamera(camera);
}

// Make this return true when this Command no longer needs to run execute()
bool SelectCamera::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void SelectCamera::End()
{
	DriverStation::ReportError("Ending SelectCamera");
	cameras->StopCamera(camera);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SelectCamera::Interrupted()
{
	DriverStation::ReportError("Interrupting SelectCamera");
	cameras->StopCamera(camera);
}
