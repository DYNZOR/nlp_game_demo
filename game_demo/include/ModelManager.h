#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <gl_core_4_3.hpp>
#include <map>
#include <memory>
#include "Model.h"


class ModelManager {

private:
	static ModelManager * pModelManager;

	std::map <const std::string, std::shared_ptr<Model>> mModels; //!< Map of models 

	//std::map <const std::string, std::shared_ptr<VertexShader>> mVertShaders;
	//std::map <const std::string, std::shared_ptr<FragmentShader>> mFragShaders;
	ModelManager();
	~ModelManager();
public:

	static ModelManager* ModelManagerInstance();

	std::shared_ptr<Model> getModelByName(std::string ksModelName);




};

#endif