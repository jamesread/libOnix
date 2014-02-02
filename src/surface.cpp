#include "common.hpp"
#include "surface.hpp"
#include <string>
#include <sstream>
#include <stdexcept>
#include <stdint.h>
#include <cmath>
#include <stdio.h>

std::string vecstr(float x, float y);

surface::surface(int w, int h, char fill) {
	this->w = w;
	this->h = h;
	this->fill(fill);
}

void surface::rot(int oriX, int oriY, int deg, char clipChar) {
	surface* rotated = new surface(this->getWidth(), this->getHeight(), 'R');
	double rotX, rotY;

	double rad = deg * M_PI / 180.0;
	double s = sin(rad);
	double c = cos(rad);

#if DEBUG
	std::cout << "deg: " << deg << " = rad: " << rad << " (sin: " << std::fixed << s << " cos: " << std::fixed << c << ")" <<std::endl;
#endif

	bool shiftX = this->getWidth() % 2;
	bool shiftY = this->getHeight() % 2;
	
	for (int srcX = 0; srcX < this->getWidth(); srcX++) {
		for (int srcY = 0; srcY < this->getHeight(); srcY++) {
			int tmpX = srcX - oriX;
			int tmpY = srcY - oriY;

			float newX = tmpX * c - tmpY * s;
			float newY = tmpY * s + tmpY * c;
			newX = round(newX);
			newY = round(newY);

			rotX = newX + oriX;
			rotY = newY + oriY;

			if (!shiftX) rotX--;
			if (!shiftY) rotY--;

			char charAtRotatedPoint = this->get(srcX, srcY, clipChar);
			rotated->set(rotX, rotY, charAtRotatedPoint);

#if DEBUG
			std::cout << "ori: " << vecstr(oriX, oriY) << "\t new: " << vecstr(newX, newY) << "\t src: " << vecstr(srcX, srcY) << "\t rot: " << vecstr(rotX, rotY) << "\t = " << this->get(rotX, rotY) << std::endl;
#endif

		}
	}

	this->fill('O');
	this->blit(0, 0, rotated);
}

void surface::shift(int x, int y) {
	surface* shifted = new surface(this->getWidth(), this->getHeight(), '!');

	this->blitQuietly(x, y, shifted);
}

void surface::replace(char find, char replace) {
	for (uint32_t i = 0; i < this->map.length(); i++) {
		if (find == this->map.at(i)) {
			this->map.replace(i, 1, 1, replace);
		}
	}
}

void surface::row(int row, std::string content) {
	for (int i = 0; i < this->w; i++) {
		this->set(i, row, content.at(i));
	}
}

void surface::fill(char fill) {
	this->map = std::string(this->w * this->h, fill);
}

int surface::getPos(int x, int y) {
	return (y * this->w) + x;
}

void surface::rect(int x, int y, int w, int h, char fill) {
	for (int row = y; row < y + h; row++) {
		this->hline(x, row, w, fill);
	}
}

void surface::hline(int x, int y, int l, char fill) {
	for (int i = x; i < (x + l); i++) {
		this->set(i, y, fill);
	}
}

void surface::vline(int x, int y, int l, char fill) {
	for (int i = y; i < (y + l); i++) {
		this->set(x, i, fill);
	}
}

void surface::border(char bchar) {
	this->border(bchar, bchar);
}

void surface::border(char vchar, char hchar) {
	this->border(0, 0, this->w - 1, this->h - 1, vchar, hchar);
}

void surface::border(int x, int y, int w, int h) {
	this->border(x, y, w, h, '#', '#');
}

void surface::border(int x, int y, int w, int h, char vchar, char hchar) {
	this->hline(x, y, w + 1, hchar);
	this->hline(x, y + h, w + 1, hchar);
	this->vline(x, y + 1, h - 1, vchar);
	this->vline(x + w, y + 1, h - 1, vchar);
}

void surface::window(int x, int y, int w, int h) {
	this->rect(x, y, w, h, ' ');
	this->border(x, y, w, h);
}

void surface::blitQuietly(int x, int y, surface* source) {
	int rx, ry;

	for (int sx = 0; sx < source->getWidth(); sx++) {
		for (int sy = 0; sy < source->getHeight(); sy++) {
			rx = x + sx;
			ry = y + sy;

			if (rx < this->getWidth() && ry < this->getHeight()) {
				char c = source->get(sx, sy);
				this->set(rx , ry, c);	
			}
		}
	}
}

void surface::blit(int x, int y, surface* source) {
	int rx, ry;

	for (int sx = 0; sx < source->getWidth(); sx++) {
		for (int sy = 0; sy < source->getHeight(); sy++) {
			rx = x + sx;
			ry = y + sy;

			this->set(rx, ry, source->get(sx, sy));	
		}
	}
}

void surface::set(uint32_t pos, char fill) {
	if (pos >= this->map.length()) {
		return;
//		std::stringstream error;
//		error << "pos is out of range: " << pos;
//		throw std::runtime_error(error.str());
	}

	this->map.replace(pos, 1, 1, fill);
}

void surface::set(int x, int y, char fill) {
	if (this->rangeCheck(x, y, "set")) {
		int pos = this->getPos(x, y);

		this->set(pos, fill);
	}
}

char surface::get(int x, int y) {
	return this->get(x, y, '?');
}

char surface::get(int x, int y, char clipChar) {
	if (this->rangeCheck(x, y, "get")) {
		return this->map.at(this->getPos(x, y));
	} else {
		return clipChar;
	}
}

bool surface::rangeCheck(int x, int y, std::string title) {
	if (x < 0 || x >= this->w) {
		return false;
	}

	if (y < 0 || y >= this->h) {
		return false;
	}

	return true;
}

bool surface::rangeCheck(int x, int y) {
	return this->rangeCheck(x, y, "???");
}

std::string surface::str() {
	std::string ret = std::string(this->map);

	for (int row = 0; row < this->h; row++) {
		ret.insert(row * (this->w + 1), "\n");
	}

	return ret;
}

std::string surface::rawstr() {
	return this->map;
}

int surface::getWidth() {
	return this->w;
}

int surface::getHeight() {
	return this->h;
}
