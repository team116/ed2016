#include <CommandBase.h>
#include <Commands/Scheduler.h>
#include <OI.h>
#include <Subsystems/HolderWheel.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/Climber.h>
#include <Subsystems/Sensors.h>
#include <Subsystems/Shooter.h>
#include <Subsystems/ShooterPitch.h>
#include <Subsystems/Cameras.h>
#include <Subsystems/Intake.h>

// Initialize a single static instance of all of your subsystems to NULL
OI* CommandBase::oi = nullptr;
Mobility* CommandBase::mobility = nullptr;
Climber* CommandBase::climber = nullptr;
Sensors* CommandBase::sensors = nullptr;
Shooter* CommandBase::shooter = nullptr;
ShooterPitch* CommandBase::shooter_pitch = nullptr;
HolderWheel* CommandBase::holder_wheel = nullptr;
Cameras* CommandBase::cameras = nullptr;
Intake* CommandBase::intake = nullptr;

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
	oi = OI::getInstance();
	mobility = Mobility::getInstance();
	climber = Climber::getInstance();
	sensors = Sensors::getInstance();
	shooter = Shooter::getInstance();
	cameras = Cameras::getInstance();
	intake = Intake::getInstance();
	holder_wheel = HolderWheel::getInstance();
}
