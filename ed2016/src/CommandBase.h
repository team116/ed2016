#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <string>
#include <Commands/Command.h>
#include <WPILib.h>

// list all subsystems here to prevent cyclical dependencies
class Climber;
class Mobility;
class Sensors;
class Shooter;
class ShooterPitch;
class HolderWheel;
class Cameras;
class OI;
class Intake;


/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command
{
public:
	CommandBase(const std::string &name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static Climber* climber;
	static Mobility* mobility;
	static Sensors* sensors;
	static Shooter* shooter;
	static ShooterPitch* shooter_pitch;
	static HolderWheel* holder_wheel;
	static Cameras* cameras;
	static OI* oi;
	static Intake* intake;
};

#endif
