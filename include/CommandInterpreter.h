#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include "SceneModel.h"
#include "SceneAnalyser.h"
#include "PyModuleData.h"

class CommandInterpreter
{
public:

	CommandInterpreter();
	~CommandInterpreter();

	void ProcessCommand(const SentenceData& dataIn, SceneAnalyser& analyser);


private:

	std::shared_ptr<SceneModel> RetrieveSceneEntity(std::string sEntityIn);
	std::shared_ptr<SceneModel> RetrieveSceneLocation(std::string sLocationIn);


};


#endif