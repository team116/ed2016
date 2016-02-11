/*
 * MobilityPIDOutput.cpp
 *
 *  Created on: Feb 10, 2016
 *      Author: strahans
 */

#include <Subsystems/MobilityPIDOutput.h>
#include <Subsystems/Mobility.h>
#include <CommandBase.h>

MobilityPIDOutput::MobilityPIDOutput(Side s) {
	side = s;
}

MobilityPIDOutput::~MobilityPIDOutput() {
	// TODO Auto-generated destructor stub
}

void MobilityPIDOutput::PIDWrite(float speed)
{
	if (side == RIGHT)
	{
		CommandBase::mobility->setRight(speed);
	}
	else
	{
		CommandBase::mobility->setLeft(speed);
	}
}
