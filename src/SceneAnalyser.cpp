#include "SceneAnalyser.h"
#include "Scene.h"
#include <memory>
#include <iterator>

SceneAnalyser::SceneAnalyser()
{

}

SceneAnalyser::~SceneAnalyser()
{

}

void SceneAnalyser::ReadScene(Scene* pSceneIn)
{
	m_SceneContentMap[1] = AnalyseScene(pSceneIn);
}

SceneContent* SceneAnalyser::AnalyseScene(Scene* pSceneIn)
{
	SceneContent* pNewContent = new SceneContent();

	std::vector<std::shared_ptr<SceneModel>>::iterator itr = pSceneIn->getModels().begin();

	for (itr; itr != pSceneIn->getModels().end(); ++itr)
	{
		pNewContent->AddObjectDescription(itr->get()->GetDescription());
	}

	return pNewContent;
}

bool SceneAnalyser::EntityExists(std::string sName)
{
	SceneContent* content = m_SceneContentMap[1];

	for (int i = 0; i < content->m_aNamedEntities.size(); ++i)
	{
		if (content->m_aNamedEntities[i].m_sName == sName)
		{
			return true;
		}
	}

	return false;
}

bool SceneAnalyser::LocationExists(std::string sLocation)
{
	return false;
}