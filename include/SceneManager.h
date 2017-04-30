/**
@file SceneManager.h
*/
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#define WINDOW_WIDTH 1920	//!< Height of window
#define WINDOW_HEIGHT 1080	//!< Width of window 

#define GLM_FORCE_RADIANS


#include "stdafx.h"
#include <gl_core_4_3.hpp>

//#include "OVR_CAPI_GL.h"

#include "AssetManager.h"
//#include "Win32_GLAppUtil.h"
//#include "Kernel\OVR_System.h"
#include <GLFW/glfw3.h>
//#include "ObjectFactory.h"
//#include <tinyxml2.h>
#include <vector>
#include <memory>
//#include "Scene.h"
#include "Camera.h"
#include <Config.h>
#include "splashScreen.h"


class Scene;

/*! \class SceneManager
\brief The Scene manager class which manages all the scenes in the engine. 
*/
class SceneManager {

protected:
	SceneManager() { pAssetManager = AssetManager::AssetManagerInstance();  }

public:

	static SceneManager* SceneManagerInstance() {
		if (!sceneManager) {
			return sceneManager = new SceneManager();
		}
		else {
			return sceneManager;
		}
	} //!< Returns a pointer to the Scene manager instance 

	void init(); //!< Initialises a GLFW window and configures some opengl and glfw settings 
	void handleInput(float t); //!< Handles keyboard and mouse user input to the system 
	void update(float fInterval /*!< Interval at which to update */); 	//!< Updates the scene at the back of the vector 
	void render();//!< Renders the scene at the back of the vector 
	void updateAI(float fInterval);
	void mainLoop(); //!< Scene manager mainloop which until the window is closed, it renders and updates the active scene

	void clean(); //!< Cleans all the scenes stored in the vector 

	void resizeGL(Camera* camera, int w, int h); //!< Resize 

	void changeScene(Scene* sceneIn /*!< Scene the switch to */); //!< Changes the scene by popping a scene from the back of the vector and pushing a new one on

	void pushScene(Scene* sceneIn  /*!< Scene to switch to */); //!< Pushes a scene onto the vector and pauses the scene that is at the back 


	double lastCursorPositionX; //!< Last position of mouse cursor on the x
	double lastCursorPositionY; //!< Last position of mouse cursor on the y
	double cursorPositionX;	//!< Position of mouse cursor on the x
	double cursorPositionY; //!< Position of mouse cursor on the y 

	AssetManager* getAssetManager() { return pAssetManager;  }

	GLFWwindow* getWindow() { return window; } //!< Returns pointer to glfw window

	Camera* getActiveSceneCamera(); //!< Returns a pointer to the camera from the active scene 


	bool running() { return bRunning; } //!< Returns true if the scenemanager is running 

	void quit() { bRunning = false;}
	void splashscreen(bool isSplashingAboutOn);
	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	//static void scroll_callback(GLFWwindow *window, double x, double y);

	// Destructor 


private:

	static SceneManager* sceneManager; //!< Pointer to scenemanger object 

	AssetManager* pAssetManager; //!< Pointer to the assets manager

	std::vector<Scene*> scenes; //!< Vector of scenes in the scenemanager 

	bool bRunning;	//!< Is the scenemanager running 

	GLFWwindow *window; //!< GLFW window 
	GLFWwindow *splash; //!< GLFW window 

	splashScreen screen;

	void loadSplashscreen();

	float pOri;
	//float camYOri;

	glm::vec3 cameraFollowDist;

	//bool bHMDLoaded; 
	//ovrSizei hmdResolution;
	//ovrSession hmdSession;
	//ovrHmdDesc hmdDescription;
	//GLuint mirrorFBO; 
	//ovrGLTexture * mirrorTexture;
	//TextureBuffer * eyeTexture[2];
	//DepthBuffer * eyeDepthBuffer[2];
	//ovrEyeRenderDesc eyeRenderDesc[2];



};

#endif