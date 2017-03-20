/**
@file Transformable.h
*/
#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

//#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>



// World axes
const glm::vec3 WORLDX = glm::vec3(1, 0, 0); // x
const glm::vec3 WORLDY = glm::vec3(0, 1, 0); // y
const glm::vec3 WORLDZ = glm::vec3(0, 0, 1); // z 

/*! \class Transformable
\brief The transformable interface that is inherited by any object that requires transformation 
*/
class Transformable
{
protected: 
	glm::vec3 vPosition; //!< The position of the object in world space

	glm::vec3 vRotation;//!< Rotation of model 
	glm::vec3 vScale; //!< Scale of model
	glm::mat4 mModelMatrix; //!< Model matrix that stores all transformations 
	glm::mat4 mRotationMatrix;

	glm::quat orientation;

	glm::vec3 vDirection;
public:
	Transformable();
	~Transformable();

	void setPosition(const float X, const float Y, const float Z); //!< Sets the position of the object using 3 floats 
	void setPosition(const glm::vec3 kPos); //!< Sets the position of the object using a vec3

	void setRotation(const float x, const float y, const float z); //!< Sets the rotation of the object
	void setRotation(glm::quat qRotation); //!< Sets the rotation of the object using a quaternion

	void setScale(glm::vec3 scaleIn); //!< Sets the scale of the object 

	void translate(const float kX, const float kY, const float kZ); //!< Translates the object using 3 floats
	void translate(const glm::vec3 kTranslate); //!< Translates the object using a glm::vec3
	void translateLR(const float kX, const float kY, const float kZ); //!< Translates the object using 3 floats
	void translateLR(const glm::vec3 kTranslate); //!< Translates the object using a glm::vec3

	void rotate(const float yaw, const float pitch, const float roll); //!< Rotates the object in increments 

	void updateDirection();

	glm::quat fromAxisAngle(glm::vec3 axis, float angle);

	float getYRot(); //!< Returns the rotation around the y-axis of a quat

	glm::vec3 getPosition();
	glm::mat4 getModelMatrix(); //!< Returns the model matrix with the model's transformations 
	
};

#endif
