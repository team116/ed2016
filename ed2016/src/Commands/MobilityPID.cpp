/*
#include <Commands/MobilityPID.h>
#include <Subsystems/MobilityPIDOutput.h>
#include <Subsystems/Sensors.h>
#include <PIDController.h>

const float MobilityPID::P_VAL = 1;
const float MobilityPID::I_VAL = 0;
const float MobilityPID::D_VAL = 0;

MobilityPID::MobilityPID()
{
	left_shark = new PIDController(P_VAL, I_VAL, D_VAL, new MobilityPIDOutput(MobilityPIDOutput::LEFT));
	right_shark  = new PIDController(P_VAL, I_VAL, D_VAL, 0.0, new MobilityPIDOutput(MobilityPIDOutput::RIGHT));

	interrupted = false;
}

// Called just before this Command runs the first time
void MobilityPID::Initialize()
{
	left_shark->SetPID(P_VAL, I_VAL, D_VAL);
	left_shark->SetOutputRange(-1.0, 1.0);
	right_shark->SetPID(P_VAL, I_VAL, D_VAL);
	right_shark->SetOutputRange(-1.0, 1.0);

	left_shark->SetContinuous(true);
	right_shark->SetContinuous(true);

	left_shark->SetInputRange(0.0, 4000.0);
	right_shark->SetInputRange(0.0, 4000.0);
}

// Called repeatedly when this Command is scheduled to run
void MobilityPID::Execute()
{
	left_shark->Enable();
	right_shark->Enable();
}

// Make this return true when this Command no longer needs to run execute()
bool MobilityPID::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void MobilityPID::End()
{
	left_shark->Disable();
	right_shark->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MobilityPID::Interrupted()
{
	End();
	interrupted = true;
}
*/
