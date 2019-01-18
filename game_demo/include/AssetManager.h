/** \file AssetManager.h
* Header file for the assetLoader class.
*/

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <memory>

#include "ModelManager.h"
#include "ShaderManager.h"

//! The assetLoader Class
/*!
This class provides access to the managers for shaders, textures, models and audio. 
*/
class AssetManager
{
private:

	static AssetManager* pAssetManager;

	/** sets all the bools to false for the input */
	AssetManager();
	~AssetManager();

	// Texture manager instance 

	ModelManager* pModelManager; //!< Model manager instance 

	ShaderManager* pShaderManager; //!< Shader manager instance

	// Audio manager instance 


	/** a map of models to be used at a later basis */
	//std::map<std::string, std::shared_ptr<modelGraphicsComponent>> models;
	/** a map of textures to be used at a later basis */
	//std::map<std::string, GLuint> texture;
	/** a map of shaders to be used at a later basis */
	//std::map<std::string, GLuint> shaders;

public:
	 
	static AssetManager* AssetManagerInstance();

	std::shared_ptr<Model> getModel(std::string sModelName) { return pModelManager->getModelByName(sModelName) ;  }
	std::shared_ptr<ShaderProgram> getShaderProgram(const char* kcProgName) { return pShaderManager->getShaderProgram(kcProgName); }

	// Texture manager getter
	// Shader manager getter 
	ShaderManager* getShaderManager() { return pShaderManager; }

};

#endif 