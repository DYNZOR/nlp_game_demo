#include "ObjectFactory.h"

std::shared_ptr<SceneObject> ObjectFactory::createObject(std::string objectName, glm::vec3 pos, glm::quat rotation, glm::vec3 scale, std::string text)
{
	return nullptr;
}

std::shared_ptr<SceneModel> ObjectFactory::createModel(std::string entityname, std::string filename, glm::vec3 pos, glm::quat rotation, glm::vec3 vScale, const char* kcShaderProg, std::string kcAiBehaviour, glm::vec3 vPos2, float fAi2)
{
	return std::shared_ptr<SceneModel>(new SceneModel(entityname,filename, pos, rotation, vScale, kcShaderProg, kcAiBehaviour, vPos2, fAi2));
}
