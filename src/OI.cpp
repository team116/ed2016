#include <cstdlib>
#include <OI.h>

OI* OI::INSTANCE = nullptr;

OI::OI()
{
	// Process operator interface input here.
}

OI* OI::getInstance()
{
	if (INSTANCE != nullptr)
	{
		INSTANCE = new OI();
	}
	return INSTANCE;
}
