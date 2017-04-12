#include "PythonEmbedder.h"
#include <iostream>
#include "PyModules.h"

PythonEmbedder::PythonEmbedder()
{
	PyImport_AppendInittab("SentenceModule", &PyInit_SentenceModule);
	Py_Initialize();

	try
	{
		ImportModules();

		// ADD ABILITY TO MANIPULATE SENTENCE DATA EXTERNALLY 
		SentenceData sentence;
		sentence.words = 0;
		sentence.sentence = "WORDS!";

		bp::object process_stnc = nlp_module.attr("ProcessString")(boost::ref(sentence)); // gets the processstring function from my python file pyfile.py

	}
	catch (bp::error_already_set const&) {

		std::string s_Error = ParsePythonException();
		std::cout << "An error in Python has occured: " << s_Error << std::endl;
	}
	
}

PythonEmbedder::~PythonEmbedder()
{

}

void PythonEmbedder::InitiateInterpreter()
{

}

void PythonEmbedder::SetPythonPath()
{
	//int setenv(const char *name, const char *value, int overwrite)
	//{
	//	int errcode = 0;
	//	if (!overwrite) {
	//		size_t envsize = 0;
	//		errcode = getenv_s(&envsize, NULL, 0, name);
	//		if (errcode || envsize) return errcode;
	//	}
	//	return _putenv_s(name, value);
	//}

	//setenv("PYTHONPATH", "C:\\Users\\DYN\Desktop\\ACI_Mini_Project\\src\\", 1);
	//setenv("PYTHONPATH", ".", 1);

	//boost::filesystem::path workingDir = boost::filesystem::absolute("./src").normalize();
	//PyObject* sysPath = PySys_GetObject("path");
	//PyList_Insert(sysPath, 0, PyBytes_FromString(workingDir.string().c_str()));

	//python::import("sys").attr("path").attr("append")("C:\\Users\\DYN\Desktop\\ACI_Mini_Project\\src");
	//PyRun_SimpleString("import sys; sys.path.append('C:\\Users\\DYN\Desktop\\ACI_Mini_Project\\src')\n");
}

void PythonEmbedder::ImportModules()
{
	sentence_module = bp::import("SentenceModule");

	nlp_module = bp::import("nlp");

}

void PythonEmbedder::Shutdown()
{

}

// Parses the value of the active python exception
// NOTE SHOULD NOT BE CALLED IF NO EXCEPTION
std::string PythonEmbedder::ParsePythonException() 
{
	PyObject *type_ptr = NULL, *value_ptr = NULL, *traceback_ptr = NULL;
	// Fetch the exception info from the Python C API
	PyErr_Fetch(&type_ptr, &value_ptr, &traceback_ptr);

	// Fallback error
	std::string ret("Unfetchable Python error");
	// If the fetch got a type pointer, parse the type into the exception string
	if (type_ptr != NULL) {
		bp::handle<> h_type(type_ptr);
		bp::str type_pstr(h_type);
		// Extract the string from the boost::python object
		bp::extract<std::string> e_type_pstr(type_pstr);
		// If a valid string extraction is available, use it 
		//  otherwise use fallback
		if (e_type_pstr.check())
			ret = e_type_pstr();
		else
			ret = "Unknown exception type";
	}
	// Do the same for the exception value (the stringification of the exception)
	if (value_ptr != NULL) {
		bp::handle<> h_val(value_ptr);
		bp::str a(h_val);
		bp::extract<std::string> returned(a);
		if (returned.check())
			ret += ": " + returned();
		else
			ret += std::string(": Unparseable Python error: ");
	}
	// Parse lines from the traceback using the Python traceback module
	if (traceback_ptr != NULL) {
		bp::handle<> h_tb(traceback_ptr);
		// Load the traceback module and the format_tb function
		bp::object tb(bp::import("traceback"));
		bp::object fmt_tb(tb.attr("format_tb"));
		// Call format_tb to get a list of traceback strings
		bp::object tb_list(fmt_tb(h_tb));
		// Join the traceback strings into a single string
		bp::object tb_str(bp::str("\n").join(tb_list));
		// Extract the string, check the extraction, and fallback in necessary
		bp::extract<std::string> returned(tb_str);
		if (returned.check())
			ret += ": " + returned();
		else
			ret += std::string(": Unparseable Python traceback");
	}
	return ret;
}

// OTHER CODE EXPERIMENTS 


// import the main module
//bp::object main_module = bp::import("__main__");
// load the dictionary object out of the main module
//bp::object main_namespace = main_module.attr("__dict__");
// run simple code within the main namespace using the boost::python::exec 


////// Import module called dog (Calling function)
//bp::object test_module = bp::import("dog");
//// >>> dog = MyPythonClass.Dog()
//bp::object test_attr = test_module.attr("Dog")();

//// >>> dog.bark("woof");
//bp::object bark_func = test_attr.attr("bark")("woof");

// call the function and extract the result
//  [sidenote: this sort of syntax is what makes boost::python so valuable]
//bp::object bark = bark_func();
//std::string output = bp::extract<std::string>(bark);
//int output = bp::extract<int>(bark);

//std::cout << output << std::endl;


//// Execute the script ///

//python::object exec_script = python::exec_file("test.py", main_namespace, main_namespace);

//python::object MyFunc = main_namespace["MyFunc"];
//python::object result = MyFunc("some_args");

//// result is a dictionary
//std::string val = python::extract<std::string>(result["val"]);