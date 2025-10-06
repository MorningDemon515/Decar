#include "Camera.h"

Camera::Camera(mdm::Vector::Vec3 camPos)
{
	this->camPos = camPos;
	camFront = mdm::Vector::Vec3(0.0f, 0.0f, -1.0f);
	camUp = mdm::Vector::Vec3(0.0f, 1.0f, 0.0f);

	angleX = 0.0f;
	angleY = 0.0f;

	quatX = mdm::Quaternion::FromAxisAngle(mdm::Vector::Vec3(0.0f, 1.0f, 0.0f), mdm::Common::ToRadian(angleX));
	quatY = mdm::Quaternion::FromAxisAngle(mdm::Vector::Vec3(1.0f, 0.0f, 0.0f), mdm::Common::ToRadian(angleY));
	quat = quatX * quatY;

	camRight = mdm::General::Normalize(mdm::Vector::Cross(camFront , camUp));
}

void Camera::Forward(float speed)
{
	camPos += camFront * speed;
}

void Camera::Back(float speed)
{
	camPos -= camFront * speed;
}

void Camera::Left(float speed)
{
	camPos -= camRight * speed;
}

void Camera::Right(float speed)
{
	camPos += camRight * speed;
}

void Camera::Pitch(float speed)
{
	angleY += speed;
}

void Camera::Yaw(float speed)
{
	angleX += speed;
}

mdm::Matrix::MATRIX Camera::Matrix()
{
	if (angleY > 89.0f)
		angleY = 89.0f;
	if (angleY < -89.0f)
		angleY = -89.0f;

	quatX = mdm::Quaternion::FromAxisAngle(mdm::Vector::Vec3(0.0f, 1.0f, 0.0f), mdm::Common::ToRadian(angleX));
	quatY = mdm::Quaternion::FromAxisAngle(mdm::Vector::Vec3(1.0f, 0.0f, 0.0f), mdm::Common::ToRadian(angleY));
	quat = quatX * quatY;

	camFront = mdm::Quaternion::RotateVector(quat, mdm::Vector::Vec3(0.0f, 0.0f, -1.0f));
	camFront = mdm::General::Normalize(camFront);

	camRight = mdm::General::Normalize(mdm::Vector::Cross(camFront, camUp));

	return mdm::Transform::ViewMatrixRH(
		camPos,
		camPos + camFront,
		camUp
	);
}