#include "stdafx.h"
#include "gl_core_4_3.hpp"

// Boost includes 
//#define BOOST_PYTHON_STATIC_LIB
//#include <Python.h>
#include <boost/python.hpp>

#include "SceneManager.h"
#include "MainScene.h"

namespace python = boost::python;



//////////////////////////////////
///////////////////////////////////////////////////////
///////  Main  ////////////////////////////////////////
///////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
	try
	{
		Py_Initialize();

		python::object main_module = python::import("__main__");

		python::object global = main_module.attr("__dict__");
		
		// Define greet function in Python.
		python::object result = exec(
			"def greet():                   \n"
			"   return 'Hello from Python!' \n",
			global, global);

		// Load the greet function from a file.
		//python::object result = exec_file("test.txt", global, global);

		// Create a reference to it.
		python::object greet = global["greet"];

		// Call it.
		std::string message = python::extract<std::string>(greet());
		std::cout << message << std::endl;


		return 0;
	}
	catch (python::error_already_set&) {

		std::cerr << ">>> Error! Uncaught exception: \n";
		PyErr_Print();
	}

		



	// https://skebanga.github.io/embedded-python-pybind11/


	//SceneManager* manager = SceneManager::SceneManagerInstance();

	//manager->init();

	//manager->changeScene(MainScene::Instance());

	//manager->resizeGL(manager->getActiveSceneCamera(), 1920, 1080);

	//manager->mainLoop();

	//manager->clean();


	// Exit program
	//exit(EXIT_SUCCESS);
}

//try 
//{
//	Py_Initialize();
//	pybind11_init();

//	StrategyServer server;

//	py::object main = py::module::import("__main__");
//	py::object globals = main.attr("__dict__");
//	//py::object module = import("strategy", "C:\\Users\\DYN\Desktop\\ACI_Mini_Project\\src\\strategy.py", globals);
//	py::object module = import("strategy", "strategy.py", globals);
//	py::object Strategy = module.attr("Strategy");
//	py::object strategy = Strategy(&server);

//	strategy.attr("eval")();

//	return 0;
//
//}
//catch (const py::error_already_set&)
//{
//	std::cerr << ">>> Error! Uncaught exception: \n";
//	PyErr_Print();
//	return 1;
//}
//

//
//enum Side
//{
//	BUY,
//	SELL
//};
//
//struct Order
//{
//	std::string symbol;
//	Side        side;
//	int         size;
//	double      price;
//	int         order_id;
//};
//
//class StrategyInstance;
//
//class StrategyServer
//{
//public:
//	void sendOrder(StrategyInstance&, const std::string& symbol, Side, int size, double price);
//private:
//	int _next_order_id = 0;
//};
//
//class StrategyInstance
//{
//public:
//	StrategyInstance(StrategyServer*);
//	virtual ~StrategyInstance() = default;
//
//	virtual void eval() = 0;
//	virtual void onOrder(const Order&) = 0;
//
//	void sendOrder(const std::string& symbol, Side, int size, double price);
//
//private:
//	StrategyServer& _server;
//};
//
/////////////////////////////////////
//
//void StrategyServer::sendOrder(StrategyInstance& instance, const std::string& symbol, Side side, int size, double price)
//{
//	// simulate sending an order, receiving an acknowledgement and calling back to the strategy instance
//
//	std::cout << "sending order to market\n";
//
//	Order order{ symbol, side, size, price, ++_next_order_id };
//	instance.onOrder(order);
//}
//
/////////////////////////////////////
//
//StrategyInstance::StrategyInstance(StrategyServer* server)
//	: _server(*server)
//{
//}
//
//void StrategyInstance::sendOrder(const std::string& symbol, Side side, int size, double price)
//{
//	_server.sendOrder(*this, symbol, side, size, price);
//}
//
//////////////////////////////////////
//
//
//class PyStrategyInstance final
//	: public StrategyInstance
//{
//	using StrategyInstance::StrategyInstance;
//
//	void eval() override
//	{
//		PYBIND11_OVERLOAD_PURE(
//			void,              // return type
//			StrategyInstance,  // super class
//			eval               // function name
//		);
//	}
//
//	void onOrder(const Order& order) override
//	{
//		PYBIND11_OVERLOAD_PURE_NAME(
//			void,              // return type
//			StrategyInstance,  // super class
//			"on_order",        // python function name
//			onOrder,           // function name
//			order              // args
//		);
//	}
//};
//
//PYBIND11_PLUGIN(StrategyFramework)
//{
//	py::module m("StrategyFramework", "Example strategy framework");
//
//	py::enum_<Side>(m, "Side")
//		.value("BUY", BUY)
//		.value("SELL", SELL)
//		;
//
//	py::class_<Order>(m, "Order")
//		.def_readonly("symbol", &Order::symbol)
//		.def_readonly("side", &Order::side)
//		.def_readwrite("size", &Order::size)
//		.def_readwrite("price", &Order::price)
//		.def_readonly("order_id", &Order::order_id)
//		;
//
//	py::class_<StrategyServer>(m, "StrategyServer")
//		;
//
//	py::class_<StrategyInstance, PyStrategyInstance>(m, "StrategyInstance")
//		.def(py::init<StrategyServer*>())
//		.def("send_order", &StrategyInstance::sendOrder)
//		;
//
//	return m.ptr();
//}
//
//py::object import(const std::string& module, const std::string& path, py::object& globals)
//{
//	py::dict locals;
//	locals["module_name"] = py::cast(module);
//	locals["path"] = py::cast(path);
//
//	py::eval<py::eval_statements>(
//		"import imp\n"
//		"new_module = imp.load_module(module_name, open(path), path, ('py', 'U', imp.PY_SOURCE))\n",
//		globals,
//		locals);
//
//	return locals["new_module"];
//}