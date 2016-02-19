#include <CommandBase.h>
#include <Commands/Scheduler.h>

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
	oi.reset(new OI());
	mobility.reset(new Mobility());
	climber.reset(new Climber());
	sensors.reset(new Sensors());
	shooter.reset(new Shooter());
	shooter_pitch.reset(new ShooterPitch());
	holder_wheel.reset(new HolderWheel());
	cameras.reset(new Cameras());
	intake.reset(new Intake());
}
