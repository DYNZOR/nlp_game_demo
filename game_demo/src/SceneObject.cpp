#include "SceneObject.h"
#include "EnumParser.h"

unsigned int SceneObject::m_uiNextValidID = 0;

SceneObject::SceneObject(const std::string entityname)
{
//	graphics = nullptr;

	EnumParser<EntityNames> parser;

	SetID(parser.ParseSomeEnum(entityname));
	m_pDescription.m_sName = entityname;


}

SceneObject::~SceneObject()
{
	
}

void SceneObject::SetID(unsigned int uiNewID)
{
	//make sure the val is equal to or greater than the next available ID
	//assert((uiNewID >= m_uiNextValidID) && "<SceneObject::SetID>: invalid ID");

	m_uiID = uiNewID;

	m_uiNextValidID = m_uiID + 1;
}