#ifndef CAMERA_H
#define CAMERA_H

#include <mdm.h>

//FPS Sytle

class Camera
{
public:
	Camera() { };
	Camera(mdm::Vector::Vec3 camPos);
	~Camera() { };

	void Forward(float speed);
	void Back(float speed);
	void Left(float speed);
	void Right(float speed);

	void Pitch(float speed);
	void Yaw(float speed);

	mdm::Matrix::MATRIX Matrix();
	mdm::Vector::Vec3 GetPos() { return camPos; };
	mdm::Vector::Vec3 GetFront() { return camFront; };

private:
	mdm::Vector::Vec3 camPos;
	mdm::Vector::Vec3 camFront;
	mdm::Vector::Vec3 camUp;

	mdm::Vector::Vec3 camRight;

	float angleX, angleY;
	mdm::Quaternion::QUATERNION quatX, quatY, quat;
};

#endif // !CAMERA_H
