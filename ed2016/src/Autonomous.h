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
		NOSHOOTING_DEFPORTCULLIS = 0,			//new, simplified list
		NOSHOOTING_DEFCHEVALDEFRISES = 64,		//NOSHOOTING means robot doesnt shoot
		NOSHOOTING_DEFMOAT = 128, 				//this list only includes everything on Dial 1 and Dial 3 (shooting and defense)
		NOSHOOTING_DEFRAMPARTS = 192,
		NOSHOOTING_DEFDRAWBRIDGE = 256,
		NOSHOOTING_DEFSALLYPORT = 320,
		NOSHOOTING_DEFROCKWALL = 384,
		NOSHOOTING_DEFROUGHTERRAIN = 448,
		SHOOTINGLOW_DEFPORTCULLIS = 1,
		SHOOTINGLOW_DEFCHEVALDEFRISES = 65,
		SHOOTINGLOW_DEFMOAT = 129,
		SHOOTINGLOW_DEFRAMPARTS = 193,
		SHOOTINGLOW_DEFDRAWBRIDGE = 257,
		SHOOTINGLOW_DEFSALLYPORT = 321,
		SHOOTINGLOW_DEFROCKWALL = 385,
		SHOOTINGLOW_DEFROUGHTERRAIN = 449,
		SHOOTINGHIGH_DEFPORTCULLIS = 2,
		SHOOTINGHIGH_DEFCHEVALDEFRISES = 66,
		SHOOTINGHIGH_DEFMOAT = 130,
		SHOOTINGHIGH_DEFRAMPARTS = 194,
		SHOOTINGHIGH_DEFDRAWBRIDGE = 258,
		SHOOTINGHIGH_DEFSALLYPORT = 322,
		SHOOTINGHIGH_DEFROCKWALL = 386,
		SHOOTINGHIGH_DEFROUGHTERRAIN = 450,
	};
}

#endif /* AUTONOMOUS_H_ */
