#include <boost/python.hpp>

namespace bp = boost::python;

struct SentenceData
{
	int words;
	std::string sentence;
};

BOOST_PYTHON_MODULE(SentenceModule)
{

	bp::class_<SentenceData>("SentenceData")
		.def_readwrite("words", &SentenceData::words)
		.def_readwrite("sentence", &SentenceData::sentence)
		;
}
