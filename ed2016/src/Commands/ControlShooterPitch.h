#ifndef ControlShooterPitch_H
#define ControlShooterPitch_H

#include <CommandBase.h>
#include <Commands/AutoShoot.h>
#include <Commands/MoveShooter.h>
#include <Commands/Shoot.h>
#include <WPILib.h>

class ControlShooterPitch: public CommandBase
{
public:
	ControlShooterPitch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	bool last_fuego_value;
	bool last_auto_aim_value;

	Shoot* shoot;
	AutoShoot* auto_shoot;

	MoveShooter* move_shooter_up;
	MoveShooter* stop_shooter;
	MoveShooter* move_shooter_down;
};

#endif
