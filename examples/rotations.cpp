#include "surface.hpp"

int main() {
	int w = 5, h = 5;
	int ox = w / 2, oy = h / 2;
	int deg = 180;

	Surface* map = new Surface(w, h, '.');
	map->set(0, 0, '1');
	map->set(w-1, 0, '2');
	map->set(0, h-1, '3');
	map->set(w-1, h-1, '4');

	map->set(ox, oy, '+');

	std::cout << "Rotating around: " << ox << ":" << oy << " by " << deg << std::endl;

	std::cout << std::endl << "Original (" << w << "x" << h << "):" << std::endl << map->str() << std::endl;
	map->rotate(ox, oy, deg, '.');
	std::cout << std::endl << "Rotated  (" << w << "x" << h << "):" << std::endl << map->str() << std::endl;
}
