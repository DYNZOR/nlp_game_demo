

#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS


#include "Transformable.h"

class Camera 
{
private:

	glm::vec3 vCameraPos;
	glm::vec3 vTarget;
	glm::vec3 vUp;

	float fFieldOfView;
	float fAspectRatio;
	float fFarPlane;
	float fNearPlane;

	glm::vec3 xAxis;
	glm::vec3 yAxis;
	glm::vec3 zAxis; 

	glm::vec3 direction;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::quat orientation;

protected:

public:
	Camera(); // Constructor 

	void setPosition(const glm::vec3& positionIn); // Set camera position
	const glm::vec3& getPosition() const; // Returns camera position

	void init(void); // Initialises camera

	glm::mat4 getViewMatrix(); // Get view matrix
	glm::mat4 getProjectionMatrix();	// Get projection matrix 

	glm::quat fromAxisAngle(glm::vec3 axis, float angle); // Return rotation quaternion 

	void move(float deltaX, float deltaY, float deltaZ);

	void zoom(const float z);
	void rotate(const float yaw, const float pitch);
	void pan(const float x, const float y);
	void roll(const float z);


	void updateViewMatrix(); // Updates view matrix 

	//void reset();

	void setNearAndFarPlanes(float fFarPlaneIn, float fNearPlaneIn);
	float getFarClippingPlane() const;
	float getNearClippingPlane() const;

	void setFieldOfView(float fFieldOfViewIn);
	float getFieldOfView() const;
	void setAspectRatio(float fAspectRatioIn);
	float getAspectRatio() const;
	
	void calc3PCamera(float playerOri, glm::vec3 playerPos, glm::vec3 followDist);
};


#endif