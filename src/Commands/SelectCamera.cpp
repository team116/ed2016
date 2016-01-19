#include "SelectCamera.h"

SelectCamera::SelectCamera(int cam)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(cameras);
	SetInterruptible(true);

	camera_num = cam;

	is_finished = false;
}

// Called just before this Command runs the first time
void SelectCamera::Initialize()
{
	is_finished = false;
	//DriverStation::ReportError("|Init SelectCamera: " + std::to_string(camera_num) + "," + std::to_string(is_finished) + "|\n");

	//DriverStation::ReportError("|Starting Camera: " + std::to_string(camera_num) + "|\n");
	cameras->StartCamera(camera_num);
}

// Called repeatedly when this Command is scheduled to run
void SelectCamera::Execute()
{
	//DriverStation::ReportError("|Executing Camera: " + std::to_string(camera_num) + "|\n");
	cameras->RunCamera(camera_num);
}

// Make this return true when this Command no longer needs to run execute()
bool SelectCamera::IsFinished()
{
	if(cameras->GetRunningCamera() != camera_num)
	{
		//DriverStation::ReportError("|Cameras running different cam number than " + std::to_string(camera_num) + "|\n");
		is_finished = true;
	}
	return is_finished;
}

// Called once after isFinished returns true
void SelectCamera::End()
{
	//DriverStation::ReportError("|Ending SelectCamera: " + std::to_string(camera_num) + "|\n");
	cameras->StopCamera(camera_num);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SelectCamera::Interrupted()
{
	//DriverStation::ReportError("|Interrupting SelectCamera: " + std::to_string(camera_num) + "|\n");
	End();
}
