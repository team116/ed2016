#ifndef OI_H
#define OI_H

#include <WPILib.h>

class OI
{
public:
	static OI* getInstance();

private:
	OI();
	static OI* INSTANCE;
};

#endif
