#ifndef SelectCamera_H
#define SelectCamera_H

#include "../CommandBase.h"
#include "WPILib.h"

class SelectCamera: public CommandBase
{
public:
	SelectCamera(int cam);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	int camera;

	IMAQdxError imaqError;
};

#endif
