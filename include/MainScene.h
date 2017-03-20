/**
@file MainScene.h
*/
#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "scene.h"
//#include "Model.h"
#include "CubeMap.h"

/*! \class MainScene
\brief A mainscene class that inherits from the scene abstract class that handles the creation, updating and rendering 
of a scene 
*/

#define MOVE_VELOCITY 3.f
#define ROTATE_VELOCITY 0.001f

class MainScene : public Scene
{
private:
	static MainScene s_MainScene; //!< A static 

	int width, height;

	// Shader manager singleton instance
	// Texture manager singleton instance
	// Audio manager 

	double lastCursorPositionX; //!< Last position of mouse cursor on the x
	double lastCursorPositionY; //!< Last position of mouse cursor on the y
	double cursorPositionX;	//!< Position of mouse cursor on the x
	double cursorPositionY; //!< Position of mouse cursor on the y 
	float pOri;
	glm::vec3 cameraFollowDist;

	//std::shared_ptr<VertexShader> vertShader;
	//std::shared_ptr<FragmentShader> fragShader;

	std::shared_ptr<CubeMap> cubeMap;	//!< A cube map object for the skybox

	std::shared_ptr<ShaderProgram> basicShaderProgram;	//!< A shader program to use for most models 
	std::shared_ptr<ShaderProgram> cubeMapShaderProgram;	//!< A shader program to use for the cube map 


	std::vector<std::shared_ptr<SceneModel>> models; 
	std::vector<std::shared_ptr<SceneModel>>::iterator modelsIt;

	std::shared_ptr<SceneModel> modelSuit; 

	ObjectFactory factory;

	Texture* gTextureDiffuse;
	Texture* gTextureSpecular;


	Camera camera;	//!< Scene camera 
	Model* plane;
	Model* suit;	// Model for the suit 
	Model* spaceStation;
	Model* dragon;

	float fAngle;

protected:

	MainScene() {}

public:

	static MainScene* Instance() {
		return &s_MainScene;
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

	virtual std::shared_ptr<SceneModel> getModel() override { return models.back(); }

	void loadSceneFromXML(const std::string ksPath);

	std::vector<std::shared_ptr<SceneModel>> getModels() { return models;  }
	std::vector<std::shared_ptr<SceneModel>>::iterator getModelsIt() { return modelsIt; }

};
#endif  