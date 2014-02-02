#include "common.hpp"
#include "surface.hpp"
#include <string>
#include <sstream>
#include <stdexcept>
#include <stdint.h>
#include <cmath>
#include <stdio.h>

std::string vecstr(float x, float y);

Surface::Surface(int w, int h, char fill) {
	this->w = w;
	this->h = h;
	this->fill(fill);
}

void Surface::rotate(int deg) {
	this->rotate(this->w / 2, this->h / 2, deg, ' ');
}

void Surface::rotate(int oriX, int oriY, int deg, char clipChar) {
	Surface* rotated = new Surface(this->getWidth(), this->getHeight(), 'R');
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

void Surface::shift(int x, int y) {
	Surface* shifted = new Surface(this->getWidth(), this->getHeight(), '!');

	this->blitQuietly(x, y, shifted);
}

void Surface::replace(char find, char replace) {
	for (uint32_t i = 0; i < this->map.length(); i++) {
		if (find == this->map.at(i)) {
			this->map.replace(i, 1, 1, replace);
		}
	}
}

void Surface::row(int row, std::string content) {
	for (int i = 0; i < this->w; i++) {
		this->set(i, row, content.at(i));
	}
}

void Surface::fill(char fill) {
	this->map = std::string(this->w * this->h, fill);
}

int Surface::getPos(int x, int y) {
	return (y * this->w) + x;
}

void Surface::rect(int x, int y, int w, int h, char fill) {
	for (int row = y; row < y + h; row++) {
		this->hline(x, row, w, fill);
	}
}

void Surface::hline(int x, int y, int l, char fill) {
	for (int i = x; i < (x + l); i++) {
		this->set(i, y, fill);
	}
}

void Surface::vline(int x, int y, int l, char fill) {
	for (int i = y; i < (y + l); i++) {
		this->set(x, i, fill);
	}
}

void Surface::border() {
	this->border('|', '-', '+');
}

void Surface::border(char bchar) {
	this->border(bchar, bchar);
}

void Surface::border(char vchar, char hchar) {
	this->border(vchar, hchar, 0);
}

void Surface::border(char vchar, char hchar, char cchar) {
	this->border(0, 0, this->w - 1, this->h - 1, vchar, hchar, cchar);
}

void Surface::border(int x, int y, int w, int h) {
	this->border(x, y, w, h, '#', '#', '#');
}

void Surface::border(int x, int y, int w, int h, char vchar, char hchar, char cchar) {
	this->hline(x, y, w + 1, hchar);
	this->hline(x, y + h, w + 1, hchar);
	this->vline(x, y + 1, h - 1, vchar);
	this->vline(x + w, y + 1, h - 1, vchar);

	if (cchar != 0) {
		this->set(0, 0, cchar);
		this->set(w, 0, cchar);
		this->set(0, h, cchar);
		this->set(w, h, cchar);
	}
}

void Surface::text(int x, int y, std::string text) {
	for (uint32_t i = 0; i < text.length(); i++) {
		this->set(x + i, y, text[i]);
	}
}

void Surface::window(int x, int y, int w, int h) {
	this->rect(x, y, w, h, ' ');
	this->border(x, y, w, h);
}

void Surface::blitQuietly(int x, int y, Surface* source) {
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

void Surface::blit(int x, int y, Surface* source) {
	int rx, ry;

	for (int sx = 0; sx < source->getWidth(); sx++) {
		for (int sy = 0; sy < source->getHeight(); sy++) {
			rx = x + sx;
			ry = y + sy;

			this->set(rx, ry, source->get(sx, sy));	
		}
	}
}

void Surface::set(uint32_t pos, char fill) {
	if (pos >= this->map.length()) {
		return;
//		std::stringstream error;
//		error << "pos is out of range: " << pos;
//		throw std::runtime_error(error.str());
	}

	this->map.replace(pos, 1, 1, fill);
}

void Surface::set(int x, int y, char fill) {
	if (this->rangeCheck(x, y, "set")) {
		int pos = this->getPos(x, y);

		this->set(pos, fill);
	}
}

char Surface::get(int x, int y) {
	return this->get(x, y, '?');
}

char Surface::get(int x, int y, char clipChar) {
	if (this->rangeCheck(x, y, "get")) {
		return this->map.at(this->getPos(x, y));
	} else {
		return clipChar;
	}
}

bool Surface::rangeCheck(int x, int y, std::string title) {
	if (x < 0 || x >= this->w) {
		return false;
	}

	if (y < 0 || y >= this->h) {
		return false;
	}

	return true;
}

bool Surface::rangeCheck(int x, int y) {
	return this->rangeCheck(x, y, "???");
}

std::string Surface::str() {
	std::string ret = std::string(this->map);

	for (int row = 0; row < this->h; row++) {
		ret.insert(row * (this->w + 1), "\n");
	}

	ret.erase(0, 1);

	return ret;
}

std::string Surface::rawstr() {
	return this->map;
}

int Surface::getWidth() {
	return this->w;
}

int Surface::getHeight() {
	return this->h;
}
