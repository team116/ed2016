#include <CommandBase.h>
#include <Commands/JoystickDrive.h>

JoystickDrive::JoystickDrive()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(mobility);

	leftInput = 0;
	rightInput = 0;
}

// Called just before this Command runs the first time
void JoystickDrive::Initialize()
{
	leftInput = 0;
	rightInput = 0;
}



// Called repeatedly when this Command is scheduled to run
void JoystickDrive::Execute()
{
	leftInput = oi->getJoystickLeftY();
	rightInput = oi->getJoystickRightY();
	mobility->setRight(rightInput);
	mobility->setLeft(leftInput);

}


// Make this return true when this Command no longer needs to run execute()
bool JoystickDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void JoystickDrive::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickDrive::Interrupted()
{

}
