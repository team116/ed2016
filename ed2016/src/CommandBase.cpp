#include <CommandBase.h>
#include <Commands/Scheduler.h>

#include <OI.h>
#include <Subsystems/Cameras.h>
#include <Subsystems/Climber.h>
#include <Subsystems/HolderWheel.h>
#include <Subsystems/Intake.h>
#include <Subsystems/IntakeRoller.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>
#include <Subsystems/Winches.h>

// Initialize a single static instance of all of your subsystems to NULL
std::unique_ptr<OI> CommandBase::oi;
std::unique_ptr<Mobility> CommandBase::mobility;
std::unique_ptr<Climber> CommandBase::climber;
std::unique_ptr<Sensors> CommandBase::sensors;
std::unique_ptr<Shooter> CommandBase::shooter;
std::unique_ptr<ShooterPitch> CommandBase::shooter_pitch;
std::unique_ptr<HolderWheel> CommandBase::holder_wheel;
std::unique_ptr<Cameras> CommandBase::cameras;
std::unique_ptr<Intake> CommandBase::intake;
std::unique_ptr<IntakeRoller> CommandBase::intake_roller;
std::unique_ptr<Winches> CommandBase::winches;
Log* CommandBase::log;

CommandBase::CommandBase(const std::string &name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

void CommandBase::init()
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	log = Log::getInstance();
	sensors.reset(new Sensors());
	mobility.reset(new Mobility());
	climber.reset(new Climber());
	shooter.reset(new Shooter());
	shooter_pitch.reset(new ShooterPitch());
	holder_wheel.reset(new HolderWheel());
	cameras.reset(new Cameras());
	intake.reset(new Intake());
	intake_roller.reset(new IntakeRoller());
	winches.reset(new Winches());

	oi.reset(new OI());
}
