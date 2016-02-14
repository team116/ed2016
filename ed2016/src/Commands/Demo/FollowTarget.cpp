#include "FollowTarget.h"
#include <Subsystems/Mobility.h>
#include <Subsystems/Cameras.h>

FollowTarget::FollowTarget()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(mobility);
}

// Called just before this Command runs the first time
void FollowTarget::Initialize()
{
	if(!cameras->canSeeGoal()) {
		mobility->setLeft(1.0);
		mobility->setRight(-1.0);
	}
}

// Called repeatedly when this Command is scheduled to run
void FollowTarget::Execute()
{
	cameras->RefreshContours();
	if(cameras->canSeeGoal()) {
		if(cameras->GetTargetX() < 0.4) {
			mobility->setLeft(-0.25);
			mobility->setRight(0.25);
		}
		else if(cameras->GetTargetX() > 0.6) {
			mobility->setLeft(0.25);
			mobility->setRight(-0.25);
		}
		else {
			mobility->setLeft(1.0);
			mobility->setRight(1.0);
		}
	}
	else {
		mobility->setLeft(1.0);
		mobility->setRight(-1.0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool FollowTarget::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void FollowTarget::End()
{
	mobility->setLeft(0.0);
	mobility->setRight(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FollowTarget::Interrupted()
{
	End();
}
