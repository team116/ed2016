#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <string>
#include <Commands/Command.h>
#include <OI.h>
#include <WPILib.h>

// list all subsystems here to prevent cyclical dependencies
class Mobility;
class Cameras;
class OI;


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
	static Mobility* mobility;
	static Cameras* cameras;
	static OI* oi;
};

#endif
