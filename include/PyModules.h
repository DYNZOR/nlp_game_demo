#include <boost/python.hpp>
#include "PyModuleData.h"

namespace bp = boost::python;

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
