#include "common.hpp"
#include "surface.hpp"

int main() {
    Surface* surface = new Surface(16, 5, '.');
    surface->border('|', '-', '+');
    surface->text(2, 2, "Hello World!");

    std::cout << surface->str() << std::endl;
}
