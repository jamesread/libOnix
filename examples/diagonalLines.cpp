#include "surface.hpp"

int main() {
	Surface* surface = new Surface(30);

	surface->dline(15, 15, 10, '/', NE);
	surface->dline(15, 15, 10, '\\', SE);
	surface->dline(15, 15, 10, '/', SW);
	surface->dline(15, 15, 10, '\\', NW);
	surface->set(15, 15, 'X');

	std::cout << surface->str() << std::endl;
}
