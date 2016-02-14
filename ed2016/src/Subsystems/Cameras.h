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

	bool canSeeGoal();
	float GetTargetX();
	float GetTargetY();
	float PitchFromHorizontal();
	float AzimuthDegreesFromTarget();
	float GetDistanceFromTarget();
	void RefreshContours();

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

	IMAQdxError imaq_error;

	std::shared_ptr<NetworkTable> grip;

	static Cameras* INSTANCE;

	struct Contour
	{
		float x;
		float y;
		float area;
	};
	Contour target;
};

#endif
