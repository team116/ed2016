#include <Subsystems/Cameras.h>
#include <RobotMap.h>
#include <Commands/SelectCamera.h>
#include <math.h>

Cameras* Cameras::INSTANCE = nullptr;

const bool kError = false;
const bool kOk = true;
const int IMAGE_WIDTH = 320;
const int IMAGE_HEIGHT = 240;
const float CAMERA_MOUNT_ANGLE = 0;//TODO: Measure exact angle on real robot
const float TARGET_HEIGHT = 0.0;//In centimeters TODO: Measure exact height at competition
const float HEIGHT_DISTANCE_RATIO = 46.25;
const float CAMERA_MOUNT_HEIGHT = 0.0;//centimeters TODO: Measure exact height on real robot

Cameras::Cameras() :
		Subsystem("Cameras")
{
	back_cam_session = 0;
	front_cam_session = 0;
	imaq_error = IMAQdxError::IMAQdxErrorInvalidPointer;

	front_cam_frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	back_cam_frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);

	camera_running = CameraDirection::NONE;

	grip = NetworkTable::GetTable("GRIP");

	//-1074360316
}

void Cameras::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Cameras::StopCamera(CameraDirection camera_dir)
{
	if (camera_dir == CameraDirection::BACK && camera_running == CameraDirection::BACK) {
		// stop image acquisition
		IMAQdxStopAcquisition(back_cam_session);
		//the camera name (ex "cam0") can be found through the roborio web interface
		imaq_error = IMAQdxCloseCamera(back_cam_session);
		if (imaq_error != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"back cam IMAQdxCloseCamera error: "
							+ std::to_string((long) imaq_error) + "\n");
			return (kError);
		}
	} else if (camera_dir == CameraDirection::FRONT && camera_running == CameraDirection::FRONT) {
		IMAQdxStopAcquisition(front_cam_session);
		imaq_error = IMAQdxCloseCamera(front_cam_session);
		if (imaq_error != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"front cam IMAQdxCloseCamera error: "
							+ std::to_string((long) imaq_error) + "\n");
			return (kError);
		}

	}
	return (kOk);
}

bool Cameras::StartCamera(CameraDirection camera_dir)
{
	if(camera_running != CameraDirection::NONE)
	{
		StopCamera(camera_running);
	}
	if (camera_dir == CameraDirection::BACK) {

		imaq_error = IMAQdxOpenCamera("cam1",
				IMAQdxCameraControlModeController, &back_cam_session);
		if (imaq_error != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"back cam IMAQdxOpenCamera error: "
							+ std::to_string((long) imaq_error) + "\n");
			return (kError);
		}
		imaq_error = IMAQdxConfigureGrab(back_cam_session);
		if (imaq_error != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"back cam IMAQdxConfigureGrab error: "
							+ std::to_string((long) imaq_error) + "\n");
			return (kError);
		}
		// acquire images
		IMAQdxStartAcquisition(back_cam_session);
		camera_running = CameraDirection::BACK;

	} else if (camera_dir == CameraDirection::FRONT) {
		imaq_error = IMAQdxOpenCamera("cam0",
				IMAQdxCameraControlModeController, &front_cam_session);
		if (imaq_error != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"front cam IMAQdxOpenCamera error: "
							+ std::to_string((long) imaq_error) + "\n");
			return (kError);
		}
		imaq_error = IMAQdxConfigureGrab(front_cam_session);
		if (imaq_error != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"front cam IMAQdxConfigureGrab error: "
							+ std::to_string((long) imaq_error) + "\n");
			return (kError);
		}
		// acquire images
		IMAQdxStartAcquisition(front_cam_session);
		camera_running = CameraDirection::FRONT;

	}
	return (kOk);
}

void Cameras::RunCamera(CameraDirection camera_dir)
{
	if(camera_dir == CameraDirection::FRONT){
		imaq_error = IMAQdxGrab(front_cam_session, front_cam_frame, true, NULL);
		if (imaq_error != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"front cam IMAQdxGrab error: "
							+ std::to_string((long) imaq_error) + "\n");
		} else {
			CameraServer::GetInstance()->SetImage(front_cam_frame);
		}
	}
	else if(camera_dir == CameraDirection::BACK){
		imaq_error = IMAQdxGrab(back_cam_session, back_cam_frame, true, NULL);
		if (imaq_error != IMAQdxErrorSuccess) {
			DriverStation::ReportError(
					"back cam IMAQdxGrab error: "
							+ std::to_string((long) imaq_error) + "\n");
		} else {
			CameraServer::GetInstance()->SetImage(back_cam_frame);
		}
	}
}

int Cameras::GetRunningCamera()
{
	return camera_running;
}

void Cameras::RefreshContours()
{
	unsigned int index = 0;
	float height = 0.0f;
	for(unsigned int x = 0; x < grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>()).size(); x++) {
		if(grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>())[x] > height) {
			height = grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>())[x];
			index = x;
		}
	}

	if(canSeeGoal()) {
		target.x = grip->GetNumberArray("vision_contours/centerX", llvm::ArrayRef<double>())[index];
		target.y = grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>())[index];
		target.area = grip->GetNumberArray("vision_contours/area", llvm::ArrayRef<double>())[index];
	}
	else {
		target.x = 0.0;
		target.y = 0.0;
		target.area = 0.0;
	}
}

//Make sure to call RefreshContours
bool Cameras::canSeeGoal()
{
	//TODO: More advanced code to make sure the contour we find is actually the goal, or handling multiple contours
	if((grip->GetNumberArray("vision_contours/area", llvm::ArrayRef<double>()).size() > 0) &&
			(grip->GetNumberArray("vision_contours/centerX", llvm::ArrayRef<double>()).size() > 0) &&
			(grip->GetNumberArray("vision_contours/centerY", llvm::ArrayRef<double>()).size() > 0)) {
		return true;
	}
	return false;
}

/* 0-1
 * 0 is left side of picture
 *
 * Make sure to call RefreshContours
 */
float Cameras::GetTargetX()
{
	if(canSeeGoal()) {
		return target.x / IMAGE_WIDTH;
	}
	DriverStation::ReportError("Error: Cannot get target X if no target in view (Do you need to call RefreshContours?)\n");
	return 0.0f; //If there is no target in view...
}

/* 0-1
 * 0 is top side of picture
 *
 * Make sure to call RefreshContours
 */
float Cameras::GetTargetY()
{
	if(canSeeGoal()) {
		return target.y / IMAGE_WIDTH;
	}
	DriverStation::ReportError("Error: Cannot get target Y if no target in view (Do you need to call RefreshContours?)\n");
	return 0.0f; //If there is no target in view...
}

//Make sure to call RefreshContours
float Cameras::PitchFromHorizontal()
{
	if(canSeeGoal()) {
		return (CAMERA_MOUNT_ANGLE + atan((TARGET_HEIGHT - CAMERA_MOUNT_HEIGHT) / GetDistanceFromTarget()));
	}
	DriverStation::ReportError("Error: Cannot calculate pitch from horizontal if no target in view (Do you need to call RefreshContours?)\n");
	return 0.0f;
}

//Make sure to call RefreshContours
float Cameras::AzimuthDegreesFromTarget()
{
	DriverStation::ReportError("Warning: AzimuthDegreesFromTarget is not implemented\n");
	return 0.0f;
}

/*
 * in centimeters
 *
 * Make sure to call RefreshContours
 */
float Cameras::GetDistanceFromTarget()
{
	if(canSeeGoal()) {
		float pixel_height = grip->GetNumberArray("vision_contours/height", llvm::ArrayRef<double>())[0];
		return HEIGHT_DISTANCE_RATIO * IMAGE_HEIGHT / pixel_height;
	}
	else {
		DriverStation::ReportError("Error: Cannot calculate distance if target is not in sight (Do you need to call RefreshContours?)\n");
		return 0.0f;
	}
}

Cameras* Cameras::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Cameras();
	}
	return INSTANCE;
}
