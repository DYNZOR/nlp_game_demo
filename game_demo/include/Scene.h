/**
@file Scene.h
*/
#ifndef SCENE_H
#define SCENE_H
#include "SceneManager.h"
#include <gl_core_4_3.hpp>

#include <GLFW/glfw3.h>
#include "Camera.h"
#include "ShaderProgram.h"
#include "3rdParty\tinyxml2.h"
#include "SceneModel.h"
#include "ObjectFactory.h"
#include "SceneAnalyser.h"

//class SceneManager;
/*! \class Scene
\brief The abstract base class scene which provides functions to handle the creation, updating and rendering of a scene which inherits from it. 
*/
class Scene
{
public:
	
    /**
      Load textures, initialize shaders, etc.
      */
    virtual void initScene(SceneManager* manager) = 0; //!< Initialises the scene by loading shader, models, cube map

    /**
      This is called prior to every frame.  Use this
      to update your animation.
      */

	virtual void handleInput(float t, GLFWwindow* getWindow) = 0; //!< Handles scene input 
    virtual void update( float t ) = 0;	//!< Updates the scene every frame 

	virtual void loadSceneFromXML(const std::string ksFilePath) = 0;

    /**
      Draw your scene.
      */
    virtual void render() = 0; //!< Renders scene
	virtual void updateAI(float t) = 0;
	virtual void dispose() = 0; //!< Cleans up scene


    /**
      Called when screen is resized
      */
    virtual void resize(int, int) = 0; //!< Resize viewport 

	virtual Camera* getCamera() = 0; //!< Returns pointer to camera 

	virtual std::shared_ptr<SceneModel> getModel() = 0;

	virtual std::vector<std::shared_ptr<SceneModel>>& getModels() = 0;
	virtual std::vector<std::shared_ptr<SceneModel>>::iterator getModelsIt() = 0;

    
protected:

	Scene() { }

};

#endif // SCENE_H