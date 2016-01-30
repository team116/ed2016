#include "ProcessVision.h"

ProcessVision::ProcessVision()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	table = NetworkTable::GetTable("GRIP/vision_contours");
}

// Called just before this Command runs the first time
void ProcessVision::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ProcessVision::Execute()
{
	if(table->GetNumberArray("area", llvm::ArrayRef<double>()).size() == 1)
	{
		DriverStation::ReportError("Target Found\n");
	}
	else if(table->GetNumberArray("area", llvm::ArrayRef<double>()).size() > 1)
	{
		DriverStation::ReportError("Warning: Multiple targets found\n");
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ProcessVision::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ProcessVision::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ProcessVision::Interrupted()
{

}
