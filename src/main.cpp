#include "common.hpp"
#include <iostream>
#include <sstream>
#include "surface.hpp"

void assert(int expected, int actual);

void testRot(int w, int h, int ox, int oy, int deg) {
	surface* map = new surface(w, h, '.');
	map->set(0, 0, '1');
	map->set(w-1, 0, '2');
	map->set(0, h-1, '3');
	map->set(w-1, h-1, '4');

	map->set(ox, oy, '+');

	std::cout << "Rotating around: " << ox << ":" << oy << std::endl;

	std::cout << std::endl << "Original (" << w << "x" << h << "):" << map->str() << std::endl;
	map->rot(ox, oy, deg, '.');
	std::cout << std::endl << "Rotated  (" << w << "x" << h << "):" << map->str() << std::endl;
}

void testRotCenter(int w, int h, int deg) {
	testRot(w, h, w / 2, h / 2, deg);
}

int main() {
	std::cout << "libOnix." << std::endl;

	testRotCenter(5, 5, 90);
	testRotCenter(5, 5, 180);
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
