/*
 * Autonomous.h
 *
 *  Created on: Jan 28, 2016
 *      Author: Siddhesh
 */

#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_


namespace Autonomous
{
	enum Defense
	{
		LOW_BAR = 0,
		PORTCULLIS = 1,
		CHEVAL_DE_FRISES = 2,
		MOAT = 3,
		RAMPARTS = 4,
		DRAWBRIDGE = 5,
		SALLY_PORT = 6,
		ROCK_WALL = 7,
		ROUGH_TERRAIN = 8
	};
	enum Goals
	{
		HIGH,
		LOW,
		NONE
	};
	enum AllAutoPlays
	{

	};
}

#endif /* AUTONOMOUS_H_ */
