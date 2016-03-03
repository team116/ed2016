#include "CrossDefense.h"
#include <Commands/Autonomous/MoveToDefense.h>
#include <Commands/DriveDistance.h>
#include <Commands/AngleIntake.h>
#include <Autonomous.h>

CrossDefense::CrossDefense(Autonomous::Defense def)
{
	log = Log::getInstance();

	AddSequential(new MoveToDefense());

	if (def == MOAT || def == RAMPARTS || def == ROUGH_TERRAIN )
	{
		AddSequential(new DriveDistance(109)); //Intentionally 2.5 feet over estimate
		log->write(Log::TRACE_LEVEL, "Crossing defense MOAT/RAMPARTS/ROUGH TERRAIN");
	}
	else if (def == PORTCULLIS)
	{
		log->write(Log::TRACE_LEVEL, "Crossing defense PORTCULLIS");
		AddSequential(new AngleIntake(75.0));		//rough estimate, probably needs to be fixed
		AddParallel(new DriveDistance(122));	//rough estimate, probably needs to be fixed
		AddSequential(new AngleIntake(50.0));		//rough estimate, probably needs to be fixed
	}
	else if (def == DRAWBRIDGE)
	{
		AddSequential(new DriveDistance(134));	//rough estimate, probably needs to be fixed
		log->write(Log::TRACE_LEVEL, "Crossing defense DRAWBRIDGE");
		//figure out how to move the drawbridge arm later
	}
	else if (def == SALLY_PORT)
	{
		AddSequential(new DriveDistance(134));	//rough estimate, probably needs to be fixed
		log->write(Log::TRACE_LEVEL, "Crossing defense SALLY_PORT");
		//figure out how to move the drawbridge arm later
	}
	else if (def == CHEVAL_DE_FRISES)
	{
		log->write(Log::TRACE_LEVEL, "Crossing defense CHEVAL_DE_FRISES");
		AddSequential(new DriveDistance(150));
		AddSequential(new AngleIntake(50));		//blah blah rough blah blah estimate
		AddSequential(new DriveDistance(122));
	}
}
