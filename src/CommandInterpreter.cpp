#include "CommandInterpreter.h"
#include <iostream>
#include "SceneManager.h"
#include "MainScene.h"
#include "AgentStates.h"

CommandInterpreter::CommandInterpreter()
{

}

CommandInterpreter::~CommandInterpreter()
{

}

void CommandInterpreter::ProcessCommand(const SentenceData& dataIn, SceneAnalyser& analyser)
{

	if (analyser.EntityExists(dataIn.sPersonEntity1))
	{

		std::shared_ptr<SceneModel> pModel = RetrieveSceneEntity(dataIn.sPersonEntity1);

		if (dataIn.sAction == "move")
		{

		}

		else if (dataIn.sAction == "rotate") 
		{
			pModel->ChangeState(Rotate_State::Instance());
		} 


		else if (dataIn.sAction == "collect")
		{

		}


	}
	else {
		std::cout << "No entity exists in the scene with name: " + dataIn.sPersonEntity1 << std::endl;
	}

}

std::shared_ptr<SceneModel> CommandInterpreter::RetrieveSceneEntity(std::string sEntityIn)
{
	//MainScene* pScene = static_cast<MainScene*>(SceneManager::SceneManagerInstance()->GetActiveScene());

	Scene* pScene = SceneManager::SceneManagerInstance()->GetActiveScene();

	std::vector<std::shared_ptr<SceneModel>>::iterator itr = pScene->getModels().begin();

	for (itr; itr != pScene->getModels().end(); ++itr)
	{

		if (itr->get()->GetDescription().m_sName == sEntityIn)
		{
			
			//return std::shared_ptr<SceneModel>(&*itr->get());
			return *itr;

			//std::shared_ptr<SceneModel> pEntityModel = std::make_shared<SceneModel>(*itr->get());
			//SceneModel pNormEntityModel = *itr->get();
			//std::shared_ptr<SceneModel> pEntityModel = std::make_shared<SceneModel>(pNormEntityModel);
			//return pEntityModel;

		}

	}
}

std::shared_ptr<SceneModel> CommandInterpreter::RetrieveSceneLocation(std::string sLocationIn)
{
	Scene* pScene = SceneManager::SceneManagerInstance()->GetActiveScene();

	std::vector<std::shared_ptr<SceneModel>>::iterator itr = pScene->getModels().begin();

	for (itr; itr != pScene->getModels().end(); ++itr)
	{

		if (itr->get()->GetDescription().m_sName == sLocationIn)
		{
			//std::shared_ptr<SceneModel> pEntityModel = std::make_shared<SceneModel>(itr->get());
			SceneModel pNormEntityModel = *itr->get();
			std::shared_ptr<SceneModel> pEntityModel = std::make_shared<SceneModel>(pNormEntityModel);
			return pEntityModel;

		}

	}
}


