#ifndef PYTHONEMBEDDER_H
#define PYTHONEMBEDDER_H

#include <boost/python.hpp>
//#include <boost/filesystem.hpp>

namespace bp = boost::python;


class PythonEmbedder
{
public:
	PythonEmbedder();
	~PythonEmbedder();

	void InitiateInterpreter();
	void SetPythonPath();

	void ImportModules();
	void Shutdown();
private:

	std::string ParsePythonException();

	bp::object sentence_module;
	bp::object nlp_module;
	bp::object nltk_module;

};	

#endif