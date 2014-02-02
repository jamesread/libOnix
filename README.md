libOnix
=======

A C++ ASCII Libraray

Text
---

Code:

	#include "common.hpp"
	#include "surface.hpp"

	void testHelloWorld() {
		Surface* surface = new Surface(16, 5, '.');
		surface->border('|', '-', '+');
		surface->text(2, 2, "Hello World!");

		std::cout << surface->str(); 
	}

Produces: 

	+--------------+
	|..............|
	|.Hello World!.|
	|..............|
	+--------------+
