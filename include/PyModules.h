#include <boost/python.hpp>

namespace bp = boost::python;

struct SentenceData
{
	std::string sentence; // Sentence to be sent to NLP Module

	std::string sAction; // Action in the sentence 
	std::string sPersonEntity1; // Gameobject entity referred. 
	std::string sPersonEntity2;
	std::string sLocation; // Gameobject location 


};

BOOST_PYTHON_MODULE(SentenceModule)
{
	bp::class_<SentenceData>("SentenceData")
		.def_readwrite("sentence", &SentenceData::sentence)
		.def_readwrite("sAction", &SentenceData::sAction)
		.def_readwrite("sPersonEntity1", &SentenceData::sPersonEntity1)
		.def_readwrite("sPersonEntity2", &SentenceData::sPersonEntity2)
		.def_readwrite("sLocation", &SentenceData::sLocation)
		;
}
