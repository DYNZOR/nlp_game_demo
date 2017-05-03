#ifndef COMMANDINTERPRETER_H
#define COMMANDINTERPRETER_H

#include "SceneModel.h"
#include "SceneAnalyser.h"
#include "PyModuleData.h"

class CommandInterpreter
{
public:

	static CommandInterpreter* CommandInterpreterInstance()
	{
		if (!pCmdIntInstance) {
			return pCmdIntInstance = new CommandInterpreter();
		}
		else {
			return pCmdIntInstance;
		}
	}



	bool ProcessCommand(const CommandResponse& dataIn, SceneAnalyser& analyser);


private:

	static CommandInterpreter* pCmdIntInstance;

	CommandInterpreter();
	~CommandInterpreter();

	std::shared_ptr<SceneModel> RetrieveSceneEntity(std::string sEntityIn);
	std::shared_ptr<SceneModel> RetrieveSceneLocation(std::string sLocationIn);


};


#endif