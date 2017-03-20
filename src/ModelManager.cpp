#include "ModelManager.h"


ModelManager * ModelManager::pModelManager;

ModelManager * ModelManager::ModelManagerInstance()
{
	if (!pModelManager)
	{
		return pModelManager = new ModelManager();
	}
	else {

		return pModelManager;
	}
}

ModelManager::ModelManager()
{

}

ModelManager::~ModelManager()
{

}

std::shared_ptr<Model> ModelManager::getModelByName(std::string ksModelName)
{
	std::shared_ptr<Model> pModel = mModels[ksModelName];

	if (!pModel)
	{
		pModel = std::make_shared <Model>(Model(ksModelName));

		mModels[ksModelName] = pModel;

		return pModel;

	}
	else {
		return pModel;
	}
}