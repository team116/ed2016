#include <CommandBase.h>
#include <Commands/Scheduler.h>
#include <OI.h>
#include <Subsystems/Mobility.h>
#include <Subsystems/Cameras.h>

// Initialize a single static instance of all of your subsystems to NULL
OI* CommandBase::oi = nullptr;
Mobility* CommandBase::mobility = nullptr;
Cameras* CommandBase::cameras = nullptr;

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
	cameras = Cameras::getInstance();

	SmartDashboard::PutData(mobility);
	SmartDashboard::PutData(cameras);
}
