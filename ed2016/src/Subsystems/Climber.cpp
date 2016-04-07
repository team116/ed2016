#include <CommandBase.h>
#include <Subsystems/Climber.h>
#include <Subsystems/Sensors.h>
#include <RobotMap.h>
#include <Log.h>

const float Climber::DEPLOY_ARM_SPEED = 0.6;
const float Climber::RETRACT_ARM_SPEED = 0.6;

const float Climber::CLIMBER_CURRENT_SPIKE_THRESHHOLD = 10.0; //Ditto

Climber::Climber():Subsystem("Climber")
{
	climber_arm_direction = Utils::VerticalDirection::V_STILL;
	climber_armed_motor = Utils::constructMotor(RobotPorts::CLIMBER_ARMED_MOTOR);
}

void Climber::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
Utils::VerticalDirection Climber::getDirectionClimber()
{
	return climber_arm_direction;
}

void Climber::setClimber(Utils::VerticalDirection direction, float speed) //function from .h to .cpp
{
	climber_arm_direction = direction;
	if (direction == Utils::VerticalDirection::UP)
	{
		climber_armed_motor->Set(speed);
	}
	else if (direction == Utils::VerticalDirection::DOWN)
	{
		climber_armed_motor->Set(-speed);
	}
	else
	{
		climber_armed_motor->Set(0.0);
	}
}

bool Climber::isClimberCurrentSpiking()
{
	Log::getInstance()->write(Log::INFO_LEVEL, "Current Climber Current"
			": %f", CommandBase::sensors->getCurrent(RobotPorts::CLIMBER_ARMED_MOTOR));
	if (CommandBase::sensors->getCurrent(RobotPorts::CLIMBER_ARMED_MOTOR) > CLIMBER_CURRENT_SPIKE_THRESHHOLD) {
		return true;
	}
	else {
		return false;
	}
}
