#include "common.hpp"
#include "surface.hpp"
#include <boost/python.hpp>

BOOST_PYTHON_MODULE(pyonix)
{
	using namespace boost::python;

	def("greeting", greeting);

	class_<Surface>("Surface", init<int, int, char>())
		.def("fill", &Surface::fill)
		.def("rect", &Surface::rect)
		.def("text", &Surface::text)
		.def("toString", &Surface::str)
		.def("__str__", &Surface::str)
	;
}
