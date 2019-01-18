#include "Transformable.h"
#include <iostream>

Transformable::Transformable()
{
	
	setPosition(0.0, 0.0, 0.0);
	//setRotation(glm::quat(0.0, glm::vec3(0.0, 0.0, 0.0)));
	setScale(glm::vec3(1.0f, 1.0f, 1.0f));

	//vDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	//orientation = glm::quat(1, glm::vec3(0.0, 0.0, 0.0));
	updateDirection();
}

Transformable::~Transformable()
{

}


void Transformable::setScale(glm::vec3 scaleIn)
{
	vScale.x = scaleIn.x;
	vScale.y = scaleIn.y;
	vScale.z = scaleIn.z;
}

void Transformable::setRotation(const float x, const float y, const float z)
{
	vRotation.x = x;
	vRotation.y = y;
	vRotation.z = z;
}

glm::quat Transformable::fromAxisAngle(glm::vec3 axis, float angle)
{
	glm::quat rotation;

	rotation.w = cos(angle / 2);
	rotation.x = sin(angle / 2) * axis.x;
	rotation.y = sin(angle / 2) * axis.y;
	rotation.z = sin(angle / 2) * axis.z;

	return rotation;
}

void Transformable::rotate(const float yaw, const float pitch, const float roll)
{
	glm::quat rotatePitch = fromAxisAngle(WORLDX, pitch);
	glm::quat normalisedPitchQuat = glm::normalize(rotatePitch);
	normalisedPitchQuat = normalisedPitchQuat * orientation;
	orientation = normalisedPitchQuat;

	glm::quat rotateYaw = fromAxisAngle(WORLDY, yaw);
	glm::quat normalisedYawQuat = glm::normalize(rotateYaw);
	normalisedYawQuat = orientation * normalisedYawQuat;
	orientation = normalisedYawQuat;

	//glm::quat rotateZ = fromAxisAngle(WORLDZ, roll);
	//glm::quat normalisedRollQuat = glm::normalize(rotateZ);
	//normalisedRollQuat = orientation * normalisedRollQuat;
	//orientation = normalisedRollQuat;

	updateDirection();
}

glm::mat4 Transformable::getModelMatrix()
{

	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), vPosition);


	//mModelMatrix = glm::translate(glm::mat4(1.0f), vPosition);

	mModelMatrix = translateMatrix * mRotationMatrix;

	//mModelMatrix = glm::rotate(mModelMatrix, vRotation.x, glm::vec3(1.0, 0.0, 0.0));
	//mModelMatrix = glm::rotate(mModelMatrix, vRotation.y, glm::vec3(0.0, 1.0, 0.0));
	//mModelMatrix = glm::rotate(mModelMatrix, vRotation.z, glm::vec3(0.0, 0.0, 1.0));

	mModelMatrix = glm::scale(mModelMatrix, vScale);
	return mModelMatrix; /*glm::scale*/
}

void Transformable::updateDirection()
{
	mRotationMatrix = glm::mat4_cast(orientation); // Rotation and Scale

	//glm::mat4 tempMat = mRotationMatrix;
	//glm::mat4 tempMat = glm::transpose(viewMatrix);

	vDirection.x = mRotationMatrix[2][0];
	vDirection.y = mRotationMatrix[2][1];
	vDirection.z = mRotationMatrix[2][2];

	//std::cout <<"X: " << vDirection.x << " Y: " << vDirection.y << " Z: " << vDirection.z <<std::endl;

	//matrix = glm::translate(matrix, vPosition);
}

void Transformable::setPosition(const float kX, const float kY, const float kZ)
{
	vPosition = glm::vec3(kX, kY, kZ);
}

void Transformable::setPosition(const glm::vec3 vPos)
{
	vPosition = vPos;
}

void Transformable::setRotation(glm::quat qRotation) //!< Sets the rotation of the object using a quaternion
{
	orientation = fromAxisAngle(glm::vec3(qRotation.x, qRotation.y, qRotation.z), qRotation.w);
	updateDirection();
}

void Transformable::translate(const float kX, const float kY, const float kZ)
{
	vPosition.x += vDirection.x * kX;
	vPosition.y += vDirection.y * kY;
	vPosition.z += vDirection.z * kZ;
}

void Transformable::translate(const glm::vec3 kTranslate)
{
	vPosition.x += vDirection.x * kTranslate.x;
	vPosition.y += vDirection.y * kTranslate.y;
	vPosition.z += vDirection.z * kTranslate.z;
}

void Transformable::translateLR(const float kX, const float kY, const float kZ)
{
	vPosition.z += vDirection.x * kX;
	vPosition.y += vDirection.y * kY;
	vPosition.x += vDirection.z * kZ;
}

void Transformable::translateLR(const glm::vec3 kTranslate)
{
	vPosition.z += vDirection.x * kTranslate.x;
	vPosition.y += vDirection.y * kTranslate.y;
	vPosition.x += vDirection.z * kTranslate.z;
}

glm::vec3 Transformable::getPosition()
{
	return glm::vec3(-vPosition.x, -vPosition.y, -vPosition.z);
}

float Transformable::getYRot()
{
	/*float angle = 2 * acos(orientation.w);
	float s = sqrt(1 - orientation.w*orientation.w);
	if (orientation.y / s == 1) return angle;
	else{
		return -1;
	}*/
	//float angle = 2 * acos(orientation.w);
	
	//float angle= asin(2 * (orientation.x*orientation.y + orientation.z*orientation.w));
	float angle = glm::eulerAngles(orientation).y;
	
	while (angle > glm::radians(360.f)) angle -= glm::radians(360.f);
	while (angle < 0) angle += glm::radians(360.f);
	std::cout << "Y:  " << glm::degrees(angle) << std::endl;
	return angle;
}