#include <Commands/EnableSensors.h>
#include <Commands/ManualOverride.h>
#include <Commands/TogglePID.h>

ManualOverride::ManualOverride(bool override)
{
	AddSequential(new TogglePID(!override));
	AddSequential(new EnableSensors(!override));
}
