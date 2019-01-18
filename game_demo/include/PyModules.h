#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "PyModuleData.h"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(SentenceModule)
{
	bp::class_<SentenceData>("SentenceData")
		.def_readwrite("sentence", &SentenceData::sentence)
		;
}

BOOST_PYTHON_MODULE(CommandResponseModule)
{
	/*bp::class_<VectorStrings>("VectorStrings")
		.def(bp::vector_indexing_suite<VectorStrings>());*/

	bp::class_<CommandResponse>("CommandResponse")
		.def_readwrite("sAction", &CommandResponse::sAction)
		.def_readwrite("sPersonEntity1", &CommandResponse::sPersonEntity1)
		.def_readwrite("sPersonEntity2", &CommandResponse::sPersonEntity2)
		.def_readwrite("sLocation", &CommandResponse::sLocation)
		.def_readwrite("bHasLocation", &CommandResponse::bHasLocation)
		.def_readwrite("bCancelAction", &CommandResponse::bCancelAction)


		// // Vectors don't work 
		//.def_readwrite("sEntities", &CommandResponse::sEntities)
		//.def_readwrite("sLocations", &CommandResponse::sLocations)
		//.def_readwrite("sActions", &CommandResponse::sActions)
		//.def_readwrite("sPresentActions", &CommandResponse::sPresentActions)
		;
}

