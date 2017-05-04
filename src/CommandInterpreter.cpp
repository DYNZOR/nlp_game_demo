#include "CommandInterpreter.h"
#include <iostream>
#include "SceneManager.h"
#include "MainScene.h"
#include "AgentStates.h"

CommandInterpreter* CommandInterpreter::pCmdIntInstance;

CommandInterpreter::CommandInterpreter()
{

}

CommandInterpreter::~CommandInterpreter()
{

}

bool CommandInterpreter::ProcessCommand(const CommandResponse& dataIn, SceneAnalyser& analyser)
{
	if (dataIn.bHasLocation == 1)
	{
		// Check entity exists
		if (analyser.EntityExists(dataIn.sPersonEntity1))
		{
			std::shared_ptr<SceneModel> pModel = RetrieveSceneEntity(dataIn.sPersonEntity1);

			// Check location exists
			if (analyser.EntityExists(dataIn.sLocation))
			{
				std::shared_ptr<SceneModel> pLocation = RetrieveSceneEntity(dataIn.sLocation);

				if (dataIn.sAction == "move")
				{
					pModel->ChangeState(Move_State::Instance(pLocation));
					return true;
				}
				else if (dataIn.sAction == "collect")
				{
					pModel->ChangeState(Collect_State::Instance(pLocation));
				}
			}
			else
			{
				std::cout << "No location exists in the scene with name: " + dataIn.sPersonEntity1 << std::endl;
				return false;
			}

		}
		else {
			std::cout << "No entity exists in the scene with name: " + dataIn.sPersonEntity1 << std::endl;
			return false;
		}
	}
	else
	{
		// Check entity exists
		if (analyser.EntityExists(dataIn.sPersonEntity1))
		{
			std::shared_ptr<SceneModel> pModel = RetrieveSceneEntity(dataIn.sPersonEntity1);

			if (dataIn.sAction == "rotate")
			{
				pModel->ChangeState(Rotate_State::Instance());
				return true;
			}
			
		} 
		else
		{
			std::cout << "No entity exists in the scene with name: " + dataIn.sPersonEntity1 << std::endl;
			return false;
		}

		
	}
	
	

}

std::shared_ptr<SceneModel> CommandInterpreter::RetrieveSceneEntity(std::string sEntityIn)
{

	Scene* pScene = SceneManager::SceneManagerInstance()->GetActiveScene();

	std::vector<std::shared_ptr<SceneModel>>::iterator itr = pScene->getModels().begin();

	for (itr; itr != pScene->getModels().end(); ++itr)
	{

		if (itr->get()->GetDescription().m_sName == sEntityIn)
		{
			return *itr;
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
			return *itr;
		}

	}
}


