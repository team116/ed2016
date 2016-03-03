#ifndef MoveToDefense_H
#define MoveToDefense_H

#include "Commands/CommandGroup.h"
#include <Log.h>


class MoveToDefense: public CommandGroup
{
public:
	MoveToDefense();
private:
	Log* log;
};

#endif
