/**
@file StartScene.h
*/
#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "scene.h"
#include "CubeMap.h"
#include "imageComponent.h"
/*! \class StartScene
\brief  A class that handles the creation, updating and rendering of the start menu 
*/

class StartScene : public Scene
{
private:
	static StartScene s_StartScene; //!< A static 

	int width, height;

	std::shared_ptr<CubeMap> cubeMap;	//!< A cube map object for the skybox

	//std::shared_ptr<ShaderProgram> basicShaderProgram;	//!< A shader program to use for most models 
	std::shared_ptr<ShaderProgram> cubeMapShaderProgram;	//!< A shader program to use for the cube map 

	std::vector<std::shared_ptr<SceneModel>> modelsToRender;

	std::shared_ptr<SceneModel> test; 
	std::shared_ptr<image> background;

	glm::mat4 matrix;
	bool start;
	Camera camera;	//!< Scene camera 

protected:
	StartScene() {}

public:

	static StartScene* Instance() {
		return &s_StartScene;
	}	//!< Returns a static pointer of a MainScene object to ensure that there can only be one instance

	// Initiate Cameras, Shader Manager, Texture manager, etc..
	void initScene(SceneManager* manager); //!< Initiates scene, loads shaders and models 
	void setLightParams();	//!< Sets the light parameters and passed to the fragment shader
	void setUpMatrices(glm::mat4 matrix/*!< A model matrix to be passed into shader*/); //!< Sets up the matrices and passes them into the vertex shader

	void handleInput(float t, GLFWwindow* getWindow); //!< Function that handles the user input 
	void update(float t /*!< Update interval*/);	//!< Update function that updates in short intervals 
	void render();	//!< Renders all drawable object in the scene 
	void updateAI(float t);
	void resize(int w, int h); //!< Resize the viewport 
	void dispose();	//!< Cleans up the scenes content 

	virtual Camera* getCamera() override { return &camera; }	//!< Returns pointer to a camera 
	virtual std::shared_ptr<SceneModel> getModel() { return test;  }

	virtual std::vector<std::shared_ptr<SceneModel>> getModels() override { return modelsToRender;  }

	void loadSceneFromXML(const std::string ksPath) { }

};
#endif  