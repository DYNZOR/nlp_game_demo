#ifndef PYTHONEMBEDDER_H
#define PYTHONEMBEDDER_H

#include <boost/python.hpp>
#include "PyModuleData.h"

namespace bp = boost::python;


class PythonEmbedder
{
public:

	static PythonEmbedder* PyEmbedderInstance()
	{
		if (!pInstance) {
			return pInstance = new PythonEmbedder();
		}
		else {
			return pInstance;
		}
	}

	void InitiateInterpreter();
	void SetPythonPath();
	void Shutdown();

	bool ExecuteScript(SentenceData& sentence, CommandResponse& response);

protected:
	PythonEmbedder();
	~PythonEmbedder();
private:

	static PythonEmbedder* pInstance;

	std::string ParsePythonException();
	void ImportModules();

	bp::object sentence_module;
	bp::object commandresponse_module;
	bp::object nlp_module;

};	

#endif