#include <Commands/ShooterPID.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/Sensors.h>
const float ShooterPID::P_VAL = 1.0;
const float ShooterPID::D_VAL = 0.0;
const float ShooterPID::I_VAL = 0.0;

ShooterPID::ShooterPID()
{
	shootPID = new PIDController(P_VAL, I_VAL, D_VAL, sensors->getShooterPIDInput(), shooter->getShooterPIDOutput());

	interrupted = false;
}

// Called just before this Command runs the first time
void ShooterPID::Initialize()
{
	shootPID->SetPID(P_VAL, I_VAL, D_VAL);
	shootPID->SetOutputRange(-1.0, 1.0);
	shootPID->SetContinuous(true);
	shootPID->SetSetpoint(0.75);
}

// Called repeatedly when this Command is scheduled to run
void ShooterPID::Execute()
{
	shootPID->Enable();
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterPID::IsFinished()
{
	if (interrupted)
	{
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void ShooterPID::End()
{
	shootPID->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterPID::Interrupted()
{
	End();
	interrupted = true;
}
