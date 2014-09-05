#include "common.hpp"
#include "surface.hpp"
#include <boost/python.hpp>

BOOST_PYTHON_MODULE(pyonix)
{
	using namespace boost::python;

	def("greeting", greeting);

	class_<Surface>("Surface", init<int, int, char>())
		.def("fill", &Surface::fill)
		.def("set", (static_cast<void (Surface::*)(int, int, char c)>(&Surface::set)))
		.def("set", (static_cast<void (Surface::*)(uint32_t, char c)>(&Surface::set)))
		.def("rect", (static_cast<void (Surface::*)(int, int, int, int, char)>(&Surface::rect)))
		.def("border", (static_cast<void (Surface::*)()>(&Surface::border)))
		.def("border", (static_cast<void (Surface::*)(char)>(&Surface::border)))
		.def("border", (static_cast<void (Surface::*)(char, char)>(&Surface::border)))
		.def("border", (static_cast<void (Surface::*)(char, char, char)>(&Surface::border)))
		.def("vline", &Surface::vline)
		.def("hline", &Surface::hline)
		.def("rect", &Surface::rect)
		.def("text", &Surface::text)
		.def("toString", &Surface::str)
		.def("rotate", (static_cast<void (Surface::*)(int)>(&Surface::rotate)))
		.def("rotate", (static_cast<void (Surface::*)(int, int, int, char)>(&Surface::rotate)))
		.def("__str__", &Surface::str)
	;
}
