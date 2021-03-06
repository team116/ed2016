#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <string>
#include <Commands/Command.h>
#include <WPILib.h>
#include <Log.h>

class Cameras;
class Climber;
class HolderWheel;
class Intake;
class IntakeRoller;
class Mobility;
class OI;
class Sensors;
class Shooter;
class ShooterPitch;
class Winches;

class CommandBase: public Command
{
public:
	CommandBase(const std::string &name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static std::unique_ptr<Climber> climber;
	static std::unique_ptr<Mobility> mobility;
	static std::unique_ptr<Sensors> sensors;
	static std::unique_ptr<Shooter> shooter;
	static std::unique_ptr<ShooterPitch> shooter_pitch;
	static std::unique_ptr<Winches> winches;
	static std::unique_ptr<HolderWheel> holder_wheel;
	static std::unique_ptr<Cameras> cameras;
	static std::unique_ptr<OI> oi;
	static std::unique_ptr<Intake> intake;
	static std::unique_ptr<IntakeRoller> intake_roller;
	static Log* log;
};

#endif
