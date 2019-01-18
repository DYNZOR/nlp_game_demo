#ifndef SCENEANALYSER_H
#define SCENEANALYSER_H

#include <unordered_map>
#include <vector>
#include "ObjectDescription.h"
#include "EntityNames.h"
#include "EnumParser.h"

class Scene;

class SceneContent
{
private:

	EnumParser<EntityNames> m_nameParser;
	EnumParser<LocationNames> m_locationParser;


public:
	SceneContent()
	{
		
	}

	std::vector<ObjectDescription> m_aNamedEntities;
	std::unordered_map<std::string, EntityNames> m_MapNamesEntities;

	void AddObjectDescription(const ObjectDescription &pNewDesc) 
	{ 
		m_MapNamesEntities[pNewDesc.m_sName] = m_nameParser.ParseSomeEnum(pNewDesc.m_sName);
		m_aNamedEntities.push_back(pNewDesc); 
	}


};

class SceneAnalyser
{
public:

	SceneAnalyser();
	~SceneAnalyser();

	void ReadScene(Scene* pSceneIn);


	bool EntityExists(std::string sName);
	bool LocationExists(std::string sLocation);

private:
	SceneContent* AnalyseScene(Scene* pSceneIn);

	std::map<unsigned int, SceneContent*> m_SceneContentMap;

};

#endif
