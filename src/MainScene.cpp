#include "stdafx.h"

#include "MainScene.h"
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <fstream>
using std::ifstream;
#include <sstream>
#include <string>
using std::string;

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "PythonEmbedder.h"
#include "SpeechRecognition.h"

using glm::vec3;

//MainScene::MainScene() { }

MainScene MainScene::s_MainScene;

void MainScene::initScene(SceneManager* manager)
{

	camera = Camera();

	gl::Enable(gl::DEPTH_TEST);

	// Load a scene from an XML file
	loadSceneFromXML("resources/xml/gameLayout.xml");

	m_SceneAnalyser.ReadScene(this);
	bool exists = m_SceneAnalyser.EntityExists("Bob");



	// Load cube map 
	cubeMap = std::make_shared<CubeMap>("moonwaw");
	cubeMap->setActiveShader(AssetManager::AssetManagerInstance()->getShaderProgram("skybox"));
	cubeMap->loadCubeMap();


	setLightParams();

	// Model data to be moved into class
	fAngle = 0.0f;

	height = 1080;
	width = 1920;

	
	plane = new Model("plane.fbx");
	plane->setPosition(0.0f, -2.0f, 0.0f);
	//plane->setRotation(0.0f, 229.4f, 0.0f);
	plane->setScale(glm::vec3(10.0f, 0.1f ,10.0f));
	plane->setActiveShader(AssetManager::AssetManagerInstance()->getShaderProgram("basic"));

	Bitmap bmp = Bitmap::bitmapFromFile("resources/textures/Floor_C.jpg");
	bmp.flipVertically();
	gTextureDiffuse = new Texture(bmp);

	Bitmap bmp2 = Bitmap::bitmapFromFile("resources/textures/Floor_S.jpg");
	bmp2.flipVertically();
	gTextureSpecular = new Texture(bmp2);

	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("texture_diffuse1", (int)0);
	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("texture_specular1", (int)1);

	lastCursorPositionX = 0.0;
	lastCursorPositionY = 0.0;
	cursorPositionX = 0.0;
	cursorPositionY = 0.0;

	cameraFollowDist = glm::vec3(0, 5, 5);
	SceneManager::SceneManagerInstance()->splashscreen(false);

	m_aSentence.push_back("move Bob to Germany");
	m_aSentence.push_back("move Bob to England");
	m_aSentence.push_back("move Bob to France");
	//m_aSentence.push_back("rotate Bob");

	//m_aSentence.push_back("stop rotating Bob");
	//m_aSentence.push_back("collect the coins Bob");
	//m_aSentence.push_back("rotate Bob");
	//m_aSentence.push_back("rotate Bob");
	//m_aSentence.push_back("rotate Bob");


}

void MainScene::setLightParams()
{
	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("viewPosition", camera.getPosition());

	vec3 worldLight = vec3(0.0f, 10.0, 5.0);
	vec3 ambientIntensity = vec3(0.5f, 0.5f, 0.5f);
	vec3 diffuseIntensity = vec3(1.0f, 1.0f, 1.0f);
	vec3 specularIntensity = vec3(1.0f, 1.0f, 1.0f);


	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("light.Position", worldLight);
	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("light.La", ambientIntensity);
	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("light.Ld", diffuseIntensity);
	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("light.Ls", specularIntensity);

	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("light.constant", 1.0f);
	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("light.linear", 0.009f);
	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("light.quadratic", 0.0032f);
}

void MainScene::setUpMatrices(glm::mat4 matrix)
{
	basicShaderProgram->setUniform("mModelMatrix", matrix);
	basicShaderProgram->setUniform("mViewMatrix", camera.getViewMatrix());
	basicShaderProgram->setUniform("mProjectionMatrix", camera.getProjectionMatrix());
}

void MainScene::update(float t)
{
	fAngle += (10.0f * t);

	for (modelsIt = models.begin(); modelsIt != models.end(); ++modelsIt)
	{
		modelsIt->get()->update(t);
	}
}

void MainScene::render()
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	// Render cube map
	AssetManager::AssetManagerInstance()->getShaderManager()->setActiveShader("skybox");

	AssetManager::AssetManagerInstance()->getShaderProgram("skybox")->setUniform("mViewMatrix", camera.getViewMatrix());
	AssetManager::AssetManagerInstance()->getShaderProgram("skybox")->setUniform("mProjectionMatrix", camera.getProjectionMatrix());
	cubeMap->render();

	// Render scene models 
	AssetManager::AssetManagerInstance()->getShaderManager()->setActiveShader("basic");

	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("mViewMatrix", camera.getViewMatrix());
	AssetManager::AssetManagerInstance()->getShaderProgram("basic")->setUniform("mProjectionMatrix", camera.getProjectionMatrix());


	for (modelsIt = models.begin(); modelsIt != models.end(); ++modelsIt)
	{
		setLightParams();
		modelsIt->get()->render();
	}


	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, gTextureDiffuse->object());

	gl::ActiveTexture(gl::TEXTURE1);
	gl::BindTexture(gl::TEXTURE_2D, gTextureSpecular->object());

	plane->render();
}

void MainScene::updateAI(float t)
{
	//std::shared_ptr<SceneModel> player = models.back();
	glm::vec3 playerPos = models.back()->getModelHandle()->getPosition();
	for (modelsIt = models.begin(); modelsIt != models.end(); ++modelsIt)
	{
		modelsIt->get()->updateAI(playerPos, t);
	}
}

void MainScene::handleInput(float t, GLFWwindow* window)
{
	//fAngle += (10.0f * t);
	glfwGetCursorPos(window, &cursorPositionX, &cursorPositionY);

	//See how much the cursor has moved
	float deltaX = (float)(lastCursorPositionX - cursorPositionX);
	float deltaY = (float)(lastCursorPositionY - cursorPositionY);

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		getModel()->getModelHandle()->translate(t * MOVE_VELOCITY, 0, t * MOVE_VELOCITY);
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		getModel()->getModelHandle()->translate(t * -MOVE_VELOCITY, 0, t * -MOVE_VELOCITY);
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		//this->getModel()->getModelHandle()->translateLR(t * -MOVE_VELOCITY, 0, t * -MOVE_VELOCITY);
		/////////////
		getModel()->getModelHandle()->rotate(PI / 2, 0, 0);
		getModel()->getModelHandle()->translate(t * MOVE_VELOCITY, 0, t * MOVE_VELOCITY);
		getModel()->getModelHandle()->rotate(-PI / 2, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		//this->getModel()->getModelHandle()->translateLR(t * MOVE_VELOCITY, 0, t * MOVE_VELOCITY);
		/////////////
		getModel()->getModelHandle()->rotate(-PI / 2, 0, 0);
		getModel()->getModelHandle()->translate(t * MOVE_VELOCITY, 0, t * MOVE_VELOCITY);
		getModel()->getModelHandle()->rotate(PI / 2, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_ENTER))
	{
		//SpeechRecognition::SpeechRecoInstance()->start_listening("WORK GODDAMNIT!");

		std::string sentence = m_aSentence[count];
		count++;

		SentenceData sentenceData;
		sentenceData.sentence = sentence;


		//sentenceData.sentence = "rotate Bob";
		CommandResponse responseData;

		PythonEmbedder::PyEmbedderInstance()->ExecuteScript(sentenceData, responseData);

		CommandInterpreter::CommandInterpreterInstance()->ProcessCommand(responseData, m_SceneAnalyser);
	}


	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		if (cameraFollowDist.z > 0)
		{
			cameraFollowDist.z -= 0.1f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		cameraFollowDist.z += 0.1f;
	}


	pOri += deltaX*ROTATE_VELOCITY;
	//camYOri += deltaY*ROTATE_VELOCITY;
	getModel()->getModelHandle()->rotate(deltaX*ROTATE_VELOCITY, 0, 0);
	getCamera()->rotate(-deltaX*ROTATE_VELOCITY, -deltaY*ROTATE_VELOCITY);

	//glm::vec3 playerPos = this->getModel()->getModelHandle()->getPosition();
	//float playerOri = this->getModel()->getModelHandle()->getYRot();
	//getActiveSceneCamera()->setPosition(glm::vec3(playerPos.x - (5 * sin(playerOri)), playerPos.y - 5, playerPos.z + (5 * cos(playerOri))));
	getCamera()->calc3PCamera(
		pOri,
		//this->getModel()->getModelHandle()->getYRot(),
		getModel()->getModelHandle()->getPosition(),
		cameraFollowDist);

	/*
	// Rotate camera in the x and y axis
	getActiveSceneCamera()->rotate(-deltaX*ROTATE_VELOCITY, -deltaY*ROTATE_VELOCITY);

	// Move camera forward and backwards
	if (glfwGetKey(window, GLFW_KEY_W))
	{
	getActiveSceneCamera()->move(t * 10, t * 10, t * 10);
	}
	else if (glfwGetKey(window, GLFW_KEY_S))
	{
	getActiveSceneCamera()->move(t*-10, t*-10, t*-10);
	}


	if (glfwGetKey(window, GLFW_KEY_UP)) {
	this->getModel()->getModelHandle()->translate(t * 2, 0, t * 2);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
	this->getModel()->getModelHandle()->translate(t * -2, 0, t * -2);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
	this->getModel()->getModelHandle()->rotate(t * 2, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
	this->getModel()->getModelHandle()->rotate(t * -2, 0, 0);
	}
	*/

	/*
	//To adjust Roll with MIDDLE mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{
	std::cout << "Middle mouse button pressed!";
	getActiveSceneCamera()->roll(deltaX*ROTATE_VELOCITY);

	}
	*/


	if (glfwGetKey(window, GLFW_KEY_G))
	{
		//changeScene(StartScene::Instance());
	}

	//Store the current cursor position
	lastCursorPositionX = cursorPositionX;
	lastCursorPositionY = cursorPositionY;


	//this->handleInput(t);
}

void MainScene::resize(int w, int h)
{
	gl::Viewport(0, 0, w, h);
	width = w;
	height = h;
	camera.setAspectRatio((float)w / h);
}

void MainScene::dispose()
{

}

void MainScene::loadSceneFromXML(const std::string filePath)
{
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile((filePath).c_str());

	// Load texture manager 
	//TextureLoader texloader;
	const char * attributeText = nullptr;

	tinyxml2::XMLNode * pRoot = xmlDoc.FirstChildElement("Root");

	if (pRoot == nullptr) {
		std::cout << "No file found" << std::endl;
	}


	tinyxml2::XMLElement * pElement = pRoot->FirstChildElement("SceneObjects");

	if (pElement == nullptr) {
		std::cout << "pElement not found." << std::endl;
	}

	tinyxml2::XMLElement * pListElement = pElement->FirstChildElement("Model");

	while (pListElement != nullptr)
	{

		glm::vec3 tempPosition;
		glm::quat tempRotation;
		glm::vec3 tempScale;
		glm::vec3 tempPos2 = glm::vec3(0, 0, 0);
		float tempAi2 = 0;
		//float tempScale;

		float outFloat;
		tinyxml2::XMLElement * pInsideListElement = pListElement->FirstChildElement("filename");
		std::string fileName = std::string(pInsideListElement->GetText());

		pInsideListElement = pInsideListElement->NextSiblingElement("name");
		std::string entityName = string(pInsideListElement->GetText());

		pInsideListElement = pInsideListElement->NextSiblingElement("positionX");
		pInsideListElement->QueryFloatText(&outFloat);
		tempPosition.x = outFloat;

		pInsideListElement = pInsideListElement->NextSiblingElement("positionY");
		pInsideListElement->QueryFloatText(&outFloat);
		tempPosition.y = outFloat;

		pInsideListElement = pInsideListElement->NextSiblingElement("positionZ");
		pInsideListElement->QueryFloatText(&outFloat);
		tempPosition.z = outFloat;


		pInsideListElement = pInsideListElement->NextSiblingElement("rotationAngle");
		pInsideListElement->QueryFloatText(&outFloat);
		tempRotation.w = outFloat;

		pInsideListElement = pInsideListElement->NextSiblingElement("rotationXAxis");
		pInsideListElement->QueryFloatText(&outFloat);
		tempRotation.x = outFloat;

		pInsideListElement = pInsideListElement->NextSiblingElement("rotationYAxis");
		pInsideListElement->QueryFloatText(&outFloat);
		tempRotation.y = outFloat;

		pInsideListElement = pInsideListElement->NextSiblingElement("rotationZAxis");
		pInsideListElement->QueryFloatText(&outFloat);
		tempRotation.z = outFloat;


		pInsideListElement = pInsideListElement->NextSiblingElement("scaleX");
		pInsideListElement->QueryFloatText(&outFloat);
		tempScale.x = outFloat;

		pInsideListElement = pInsideListElement->NextSiblingElement("scaleY");
		pInsideListElement->QueryFloatText(&outFloat);
		tempScale.y = outFloat;

		pInsideListElement = pInsideListElement->NextSiblingElement("scaleZ");
		pInsideListElement->QueryFloatText(&outFloat);
		tempScale.z = outFloat;


		pInsideListElement = pInsideListElement->NextSiblingElement("shaderProgram");
		std::string programName = std::string(pInsideListElement->GetText());

		pInsideListElement = pInsideListElement->NextSiblingElement("aiBehaviour");
		std::string aiBehaviour = std::string(pInsideListElement->GetText());

		if (aiBehaviour != "none" && aiBehaviour != "turret")
		{
			pInsideListElement = pInsideListElement->NextSiblingElement("pos2X");
			pInsideListElement->QueryFloatText(&outFloat);
			tempPos2.x = outFloat;

			pInsideListElement = pInsideListElement->NextSiblingElement("pos2Y");
			pInsideListElement->QueryFloatText(&outFloat);
			tempPos2.y = outFloat;

			pInsideListElement = pInsideListElement->NextSiblingElement("pos2Z");
			pInsideListElement->QueryFloatText(&outFloat);
			tempPos2.z = outFloat;


			pInsideListElement = pInsideListElement->NextSiblingElement("ai2");
			pInsideListElement->QueryFloatText(&outFloat);
			tempAi2 = outFloat;
		}

		models.push_back(factory.createModel(entityName,fileName, tempPosition, tempRotation, tempScale, programName.c_str(), aiBehaviour.c_str(), tempPos2, tempAi2));
		pListElement = pListElement->NextSiblingElement("Model");
	}
}

