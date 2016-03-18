//Mettaton would be proud.
#include "Dance.h"
#include <Commands/Autonomous/Dance.h>
#include <Commands/TurnDegrees.h>
#include <Commands/DriveDistance.h>

Dance::Dance()
{
	Bob = new Timer();
	int STOP = 15000;
	int move,dir = 0;

	Bob->Start();

	while(Bob->Get() < STOP)
	{
			move = rand() % 1;
			if(move == 0)
			{
				AddSequential(new DriveDistance(60));
				AddSequential(new DriveDistance(-60));
			}
			if(move == 1)
			{
				dir = rand() % 360+360;
				AddSequential(new TurnDegrees(dir));
			}
	}
}
/*
 * Guess who's back?
 * Back again
 * Shady's back
 * Tell a friend
 * Now everyone report to the dance floor
 * To the dance floor, to the dance floor
 * Now everyone report to the dance floor
 * Alright Stop!.....Pajama time
*/
