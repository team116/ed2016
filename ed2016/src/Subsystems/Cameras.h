#ifndef Cameras_H
#define Cameras_H

#include <Commands/Subsystem.h>
#include <WPILib.h>

class Cameras: public Subsystem
{
public:
	Cameras();
	enum CameraDirection
	{
		NONE,
		FRONT,
		BACK
	};
	void InitDefaultCommand();

	bool StopCamera(CameraDirection camera_dir);
	bool StartCamera(CameraDirection camera_dir);
	void RunCamera(CameraDirection camera_dir);

	int GetRunningCamera();



	static Cameras* getInstance();

private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	IMAQdxSession front_cam_session;
	IMAQdxSession back_cam_session;

	CameraDirection camera_running;

	Image *front_cam_frame;
	Image *back_cam_frame;

	IMAQdxError imaqError;

	static Cameras* INSTANCE;
};

#endif