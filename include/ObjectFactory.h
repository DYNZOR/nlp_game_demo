/** \file ObjectFactory.h
* Header file for the ObjectFactory class.
*/

#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H


#include "AssetManager.h"

#include "SceneObject.h"
#include <string>
#include <sstream>
#include <memory>
#include "glm/glm.hpp"

#include "SceneModel.h"
#include "SceneLight.h"

//! Object Factory class
/*!
	This class uses the object factory pattern for creating various scene objects 
*/
class ObjectFactory
{
private:

public:

	/**
	creates a game object
	\param objectName The position of the object
	\param pos The position of the object deafault is the origin
	\param rotaion The rotaion of the object deafault is none
	\param scale The scale of the object deafault is one
	\param text The text of the object deafault is none
	*/
	std::shared_ptr<SceneObject> createObject(std::string objectName, glm::vec3 pos = glm::vec3(0), glm::quat rotation = glm::quat(0, glm::vec3(0, 0, 0)), glm::vec3 scale = glm::vec3(1), std::string text = "");
	std::shared_ptr<SceneModel> createModel(std::string objectName, glm::vec3 pos, glm::quat rotation, glm::vec3 vScale, const char* progName, std::string aiBehaviour, glm::vec3 vPos2, float fAi2);
	//std::shared_ptr<SceneLight> createLight(std::string objectName, glm::vec3 pos = glm::vec3(0), glm::quat rotation = glm::quat(0, glm::vec3(0, 0, 0)), glm::vec3 scale = glm::vec3(1), std::string text = "");




};

#endif OBJECTFACTORY_H