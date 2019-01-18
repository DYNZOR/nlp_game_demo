
#define _USE_MATH_DEFINES
#include <cmath>


#include "Config.h"
#include "Camera.h"
#include <iostream>


Camera::Camera()
{
	init();
}

void Camera::init(void)
{
	// Initialise camera axes
	//xAxis = WORLDX;
	//yAxis = WORLDY;
	//zAxis = WORLDZ;

	// Initialise camera position
	vCameraPos = glm::vec3(0.0, -5.0f, -8.0f);
	direction = glm::vec3(0.0, 0.0, 0.0);

	// Initialise orientation quaternion 
	orientation = glm::quat(1.0, 0.0, 0.0, 0.0);

	// Setting up projection matrix 
	fFieldOfView = glm::radians(50.0f);
	fNearPlane = 0.01f;
	fFarPlane = 2000.0f;
	fAspectRatio = 4.0f / 3.0f;

	projectionMatrix = glm::perspective(fFieldOfView, fAspectRatio, fNearPlane, fFarPlane);

	updateViewMatrix();


}

// Returns rotation quaternion 
glm::quat Camera::fromAxisAngle(glm::vec3 axis, float angle) {

	/*TO DO */
	/*Need to return a Quaternion which will be used to change the camera orientation
	It will represent a rotation by 'angle' radians around the vector 'axis'
	*/

	glm::quat rotation;

	rotation.w = cos(angle / 2);
	rotation.x = sin(angle / 2) * axis.x;
	rotation.y = sin(angle / 2) * axis.y;
	rotation.z = sin(angle / 2) * axis.z;

	return rotation;
}

void Camera::zoom(const float z)
{
	vCameraPos += zAxis * z;

	std::cout << vCameraPos.z << std::endl;

	updateViewMatrix();
}

void Camera::rotate(const float yaw, const float pitch)
{

	glm::quat rotatePitch = fromAxisAngle(WORLDX, pitch);
	glm::quat normalisedPitchQuat = glm::normalize(rotatePitch);

	normalisedPitchQuat = normalisedPitchQuat * orientation;
	orientation = normalisedPitchQuat;

	glm::quat rotateYaw = fromAxisAngle(WORLDY, yaw);
	glm::quat normalisedYawQuat = glm::normalize(rotateYaw);

	normalisedYawQuat = orientation * normalisedYawQuat;
	orientation = normalisedYawQuat;

	updateViewMatrix();
}

void Camera::pan(const float x, const float y)
{
	vCameraPos += xAxis * x;
	vCameraPos += yAxis * -y;

	updateViewMatrix();
}

void Camera::roll(const float z)
{
	/* TO DO */
	/* The middle mouse button is set up to call this method
	in order to roll the camera around its z-axis
	This requires similar processing to the rotate(...) method above
	but, of course, should update the camera 'orientation' with
	a roll
	*/

	glm::quat rotateZ = fromAxisAngle(WORLDZ, z);
	glm::quat normalisedRollQuat = glm::normalize(rotateZ);

	normalisedRollQuat = orientation * normalisedRollQuat;

	orientation = normalisedRollQuat;

	updateViewMatrix();
}

void Camera::move(float deltaX, float deltaY, float deltaZ)
{

	vCameraPos.x += (direction.x * deltaX);
	vCameraPos.y += (direction.y * deltaY);
	vCameraPos.z += (direction.z * deltaZ);
}


// Updates view matrix 
void Camera::updateViewMatrix()
{
	//Construct the view matrix from orientation quaternion and position vector

	//First get the matrix from the 'orientation' Quaternion
	//This deals with the rotation and scale part of the view matrix
	viewMatrix = glm::mat4_cast(orientation); // Rotation and Scale

	glm::mat4 tempMat = glm::transpose(viewMatrix);

	direction.x = tempMat[2][0];
	direction.y = tempMat[2][1];
	direction.z = tempMat[2][2];



	viewMatrix = glm::translate(viewMatrix, vCameraPos);

	////Extract the camera coordinate axes from this matrix
	//xAxis = glm::vec3(viewMatrix[0][0], viewMatrix[0][1], viewMatrix[0][2]);
	//yAxis = glm::vec3(viewMatrix[1][0], viewMatrix[1][1], viewMatrix[1][2]);
	//zAxis = glm::vec3(viewMatrix[2][0], viewMatrix[2][1], viewMatrix[2][2]);

	////And use this and current camera position to set the translate part of the view matrix
	//viewMatrix[3][0] = -glm::dot(xAxis, vCameraPos); //Translation x
	//viewMatrix[3][1] = -glm::dot(yAxis, vCameraPos); //Translation y
	//viewMatrix[3][2] = -glm::dot(zAxis, vCameraPos); //Translation z
}

void Camera::setPosition(const glm::vec3& positionIn)
{
	vCameraPos = positionIn;
}

const glm::vec3& Camera::getPosition() const
{
	return vCameraPos;
}

glm::mat4 Camera::getViewMatrix()
{
	updateViewMatrix();
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::setFieldOfView(float fFieldOfViewIn)
{
	fFieldOfView = fFieldOfViewIn;
}

float Camera::getFieldOfView() const
{
	return fFieldOfView;
}

void Camera::setAspectRatio(float fAspectRatioIn)
{
	//assert(fAspectRatioIn > 0.0f);
	fAspectRatio = fAspectRatioIn;
}

float Camera::getAspectRatio() const
{

	return fAspectRatio;
}


void Camera::setNearAndFarPlanes(float fFarPlaneIn, float fNearPlaneIn)
{
	//assert(fNearPlane > 0.0f);
	//assert(fFarPlane > fNearPlane);

	fFarPlane = fFarPlaneIn;
	fNearPlane = fNearPlaneIn;
}

float Camera::getFarClippingPlane() const
{
	return fFarPlane;
}

float Camera::getNearClippingPlane() const
{
	return fNearPlane;
}

void printVector(const glm::vec3 vecIn)
{
	std::cout << "X: " << vecIn.x << " " << "Y: " << vecIn.y << " " << "Z: " << vecIn.z << std::endl << std::endl;
}

void Camera::calc3PCamera(float playerOri, glm::vec3 playerPos, glm::vec3 followDist)
{
	setPosition(glm::vec3(
		playerPos.x - (followDist.z * sin(playerOri)),
		playerPos.y - followDist.y,
		playerPos.z - (followDist.z * cos(playerOri))
		));
	//std::cout << playerOri << std::endl;

}