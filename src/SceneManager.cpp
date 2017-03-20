#include "SceneManager.h"

#include "StartScene.h"
#include <iostream>

#include "splashScreen.h"


#define MOVE_VELOCITY 3.f
#define ROTATE_VELOCITY 0.001f

SceneManager* SceneManager::sceneManager;

void SceneManager::init()
{
	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);
	glfwWindowHint(GLFW_VISIBLE, FALSE); //hides the window
	glfwWindowHint(GLFW_DECORATED, TRUE);
	glfwWindowHint(GLFW_SAMPLES, 8);

	// Open the window
	std::string title = "Rocket Powered Engine";

	bool bIsFullScreen;

	bIsFullScreen = true;

	if (bIsFullScreen)
	{

		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), glfwGetPrimaryMonitor(), NULL);

	}
	else {

		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), NULL, NULL);

	}


	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);


	// Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) {
		//Claen up and abort
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 0, 0);


	//glfwSetKeyCallback(window, key_callback);
	//glfwSetScrollCallback(window, scroll_callback);


	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	lastCursorPositionX = 0.0;
	lastCursorPositionY = 0.0;
	cursorPositionX = 0.0;
	cursorPositionY = 0.0;

	cameraFollowDist = glm::vec3(0, 5, 5);

	//gl::Enable(gl::MULTISAMPLE);

	bRunning = true;

	//loadSplashscreen();
}

void SceneManager::changeScene(Scene* sceneIn)
{
	if (!scenes.empty())
	{
		//scenes.back()->Cleanup();
		scenes.pop_back();
	}

	scenes.push_back(sceneIn);
	scenes.back()->initScene(this);

}

void SceneManager::pushScene(Scene* sceneIn)
{
	if (!scenes.empty())
	{
		//scenes.back()->Pause();
	}

	scenes.push_back(sceneIn);
	//scenes.back()->initScene();
}


void SceneManager::handleInput(float t)
{
	//Get the current cursor position
	

	scenes.back()->handleInput(t, window);


}

void SceneManager::update(float fInterval)
{
	scenes.back()->update(fInterval);
}

void SceneManager::render()
{
	scenes.back()->render();
}

void SceneManager::updateAI(float t)
{
	scenes.back()->updateAI(t);
}


void SceneManager::mainLoop()
{
	float fLastTime = (float)glfwGetTime();

	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {


		float fCurrentTime = (float)glfwGetTime();
		float fInterval = fCurrentTime - fLastTime;

		handleInput(fInterval);

		update(fInterval);

		render();
		updateAI(fInterval);

		glfwSwapBuffers(window);
		glfwPollEvents();

		fLastTime = fCurrentTime;
	}
}

void SceneManager::mainLoopVR()
{
	float fLastTime = (float)glfwGetTime();

	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {


		float fCurrentTime = (float)glfwGetTime();
		float fInterval = fCurrentTime - fLastTime;

		handleInput(fInterval);

		update(fInterval);

		render();
		updateAI(fInterval);



		glfwSwapBuffers(window);
		glfwPollEvents();

		fLastTime = fCurrentTime;
	}
}

void SceneManager::clean()
{
	// Cleanup all scenes
	while (!scenes.empty()) {
		//scenes.back()->Cleanup(); // FINISH CLEAN UP FUNCTION 
		scenes.pop_back();
	}

	printf("Cleaning scene manager...");

	glfwTerminate();
}

void SceneManager::resizeGL(Camera* camera, int w, int h)
{
	scenes.back()->resize(w, h);
}

//void SceneManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//
//	if (key == GLFW_KEY_W)
//	{
//
//		
//		getActiveSceneCamera()->
//	}
//}

//void SceneManager::scroll_callback(GLFWwindow *window, double x, double y)
//{
//	getActiveSceneCamera()->zoom((float)y*0.5f);
//}

Camera* SceneManager::getActiveSceneCamera()
{
	return scenes.back()->getCamera();
}

void SceneManager::splashscreen(bool isSplashingAboutOn)
{
	if (!isSplashingAboutOn)
	{
		
		glfwShowWindow(window);
		//glfwHideWindow(splash);
	}
	else
	{
		glfwMakeContextCurrent(splash);
		glfwShowWindow(splash);
		screen.initScene();
		screen.render();
		glfwSwapBuffers(splash);
		glfwPollEvents();
		glfwHideWindow(window);
		glfwMakeContextCurrent(window);
	}
}

void SceneManager::loadSplashscreen()
{
	//set the clear colour
	gl::ClearColor(1.f, 0.5f, 0.5f, 1.0f);

	screen.initScene();
	screen.render();
	glfwSwapBuffers(splash);
	glfwPollEvents();
	glfwMakeContextCurrent(window);
	splashscreen(false);
}