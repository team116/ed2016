/*
 * OperateClimber.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#include <Commands/OperateClimber.h>
#include <Subsystems/Climber.h>

OperateClimber::OperateClimber(Climber::ClimberMechanismDirection dir) {
	Requires(climber);
	direction = dir;
	interrupted = false;
}

OperateClimber::~OperateClimber() {
	// TODO Auto-generated destructor stub
}

void OperateClimber::Initialize()
{

}

void OperateClimber::Execute()
{
	climber->setClimber(direction);
}

bool OperateClimber::IsFinished()
{
	if(interrupted)
	{
		return true;
	}
	return false;
}

void OperateClimber::End()
{
	climber->setClimber(Climber::CLIMBER_ARM_STILL);
}

void OperateClimber::Interrupted()
{
	End();
	interrupted = true;
}
