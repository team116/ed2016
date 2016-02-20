#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <string>
#include <Commands/Command.h>
#include <WPILib.h>
#include <OI.h>

#include <Subsystems/Cameras.h>
#include <Subsystems/Climber.h>
#include <Subsystems/HolderWheel.h>
#include <Subsystems/Intake.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>

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
	static std::unique_ptr<Climber> climber;
	static std::unique_ptr<Mobility> mobility;
	static std::unique_ptr<Sensors> sensors;
	static std::unique_ptr<Shooter> shooter;
	static std::unique_ptr<ShooterPitch> shooter_pitch;
	static std::unique_ptr<HolderWheel> holder_wheel;
	static std::unique_ptr<Cameras> cameras;
	static std::unique_ptr<OI> oi;
	static std::unique_ptr<Intake> intake;
};

#endif
