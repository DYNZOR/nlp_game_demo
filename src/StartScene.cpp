#include "stdafx.h"
#include <cstdio>
#include <cstdlib>

#include "StartScene.h"
#include "MainScene.h"
#include "GuiManager.h"
#include "Button.h"
#include <string>
using std::string;

using glm::vec3;

StartScene StartScene::s_StartScene;

void StartScene::initScene(SceneManager* manager)
{
	//textRenderer::getInstance()->Load("resources/font/arial.ttf",15);
	camera = Camera();

	gl::Enable(gl::DEPTH_TEST);
	int w;
	int h;
	background = std::make_shared<image>("resources/textures/background.png", w, h);
	matrix = glm::scale(glm::vec3(900, 800, 0));
	setLightParams();
	glm::ivec2 position(200,200);
	glm::ivec2 widthHeight(200, 200);
	std::string passiveTexturePath = "resources/textures/block.png" ;
	std::string activeTexturePath = "resources/textures/blockActive.png";
	std::string text = "Hello";
	//Button but(position, widthHeight, passiveTexturePath, activeTexturePath, text);
	//GuiManager::GuiManagerInstance()->addButton(but);



	start = true;
}

void StartScene::setLightParams()
{

}

void StartScene::setUpMatrices(glm::mat4 matrix)
{	

}

void StartScene::update(float t)
{

	//camera.rotate(5 * t, 0.0);
	//	spaceStation->move(0.0f, 0.0f, fAngle);
}

void StartScene::updateAI(float t)
{

}

void StartScene::render()
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	//background->render(matrix);
	//GuiManager::GuiManagerInstance()->renderGUI();
}

void StartScene::handleInput(float t, GLFWwindow* window)
{
	//fAngle += (10.0f * t);
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		if (!start)
		{
			start = true;
			//GuiManager::GuiManagerInstance()->buttonUp();
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		if (start)
		{
			start = false;
			//GuiManager::GuiManagerInstance()->buttonDown();
		}
	}

	if (glfwGetKey(window, GLFW_KEY_ENTER))
	{
		if (start)
		{
			SceneManager::SceneManagerInstance()->splashscreen(true);
			SceneManager::SceneManagerInstance()->changeScene(MainScene::Instance());	
		}
	}
	if (glfwGetKey(window, GLFW_KEY_ENTER))
	{
		if (!start)
		glfwDestroyWindow(window);
	}

}

void StartScene::resize(int w, int h)
{
	gl::Viewport(0, 0, w, h);
	width = w;
	height = h;
	camera.setAspectRatio((float)w / h);
}

void StartScene::dispose()
{

}

