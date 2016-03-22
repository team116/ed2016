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
	float GetTargetWidth();
	float PitchFromHorizontal();
	float HorizontalPixelsFromTarget();
	float GetDistanceFromTarget();
	void RefreshContours();

	int GetRunningCamera();

	static const int IMAGE_WIDTH;
	static const int IMAGE_HEIGHT;
	static const float TARGET_WIDTH;
	static const float TARGET_HEIGHT;//Height of the actual target
	static const float TARGET_ELEVATION;//Height of the target above the floor
	static const float TOWER_TO_GOAL_DISTANCE;

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

	struct Contour
	{
		float x;
		float y;
		float area;
		float width;
	};
	Contour target;
};

#endif
