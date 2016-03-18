/*
 * JoystickXTurn.cpp
 *
 *  Created on: Mar 15, 2016
 *      Author: amanzeb
 */

#include <CommandBase.h>
#include <Commands/JoystickTurn.h>
#include <OI.h>
#include <Subsystems/Mobility.h>
#include <RobotMap.h>

JoystickTurn::JoystickTurn(JoystickDirectZ joystick)
{

	Requires(&*mobility);
	curr_right_speed = 0.0;
	curr_left_speed = 0.0;

	joystick_value = 0.0;

	joystick_used = joystick;
	speed_multiplyer = 0.75;
}

void JoystickTurn::Initialize()
{

}

void JoystickTurn::Execute()
{
	switch(joystick_used){
	case JoystickTurn::LEFT:
		joystick_value = oi ->getJoystickLeftZ();
	break;
	case JoystickTurn::RIGHT:
		joystick_value = oi ->getJoystickRightZ();
		break;
	}
	mobility->setLeft(joystick_value * speed_multiplyer * -1);
	mobility->setRight(joystick_value * speed_multiplyer);
}
bool JoystickTurn::IsFinished()
{
	return false;
}

void JoystickTurn::End()
{
	log->write(Log::TRACE_LEVEL, "JoystickXTurn Ended");
}

void JoystickTurn::Interrupted()
{
	log->write(Log::TRACE_LEVEL, "JoystickXTurn Interrupted");
}
