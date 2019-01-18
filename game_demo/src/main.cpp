#include "stdafx.h"
#include "gl_core_4_3.hpp"
#include "SceneManager.h"
#include "MainScene.h"

#include "SpeechRecognition.h"

//////////////////////////////////
///////////////////////////////////////////////////////
///////  Main  ////////////////////////////////////////
///////////////////////////////////////////////////////
int main(int argc, char ** argv)
{

	//SpeechRecognition::SpeechRecoInstance();

	SceneManager* pSceneManager = SceneManager::SceneManagerInstance();

	pSceneManager->init();

	pSceneManager->changeScene(MainScene::Instance());

	pSceneManager->mainLoop();

	pSceneManager->clean();

	// Exit program
	exit(EXIT_SUCCESS);
}