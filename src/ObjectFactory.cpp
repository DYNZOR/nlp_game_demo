#include "ObjectFactory.h"

std::shared_ptr<SceneObject> ObjectFactory::createObject(std::string objectName, glm::vec3 pos, glm::quat rotation, glm::vec3 scale, std::string text)
{
	//std::string buf;
	//std::stringstream ss(objectName);
	//ss >> buf;

	//if (objectName == "camera")
	//{
	//	//return std::shared_ptr<gameCam>(new gameCam(pos, rotaion, scale.x));
	//}

	//else if (objectName == "sceneLight")
	//{
	//	//return std::shared_ptr<sceneLight>(new sceneLight());
	//}

	//else if (objectName == "sceneObject")
	//{
	//	//ss >> buf;
	//	return std::shared_ptr<SceneModel>(new SceneModel(buf, pos, rotaion, scale.x));
	//}


	return nullptr;
}

std::shared_ptr<SceneModel> ObjectFactory::createModel(std::string objectName, glm::vec3 pos, glm::quat rotation, glm::vec3 vScale, const char* kcShaderProg, std::string kcAiBehaviour, glm::vec3 vPos2, float fAi2)
{
	return std::shared_ptr<SceneModel>(new SceneModel(objectName, pos, rotation, vScale, kcShaderProg, kcAiBehaviour, vPos2, fAi2));
}
