#include "common.hpp"
#include <iostream>
#include <sstream>
#include "surface.hpp"

void testHelloWorld();

char const* greeting() {
	return "Salutations, from libOnix.";
}

std::string vecstr(float x, float y ) {
	std::stringstream output;

	output << "[x:" << x << ", y: " << y << "]";

	return output.str();
}

void assert(int expected, int actual) {
	if (expected != actual) {
		std::cout << "Expected: " << expected << ", got: " << actual << std::endl;
	}
}
