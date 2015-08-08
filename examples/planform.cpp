#include "surface.hpp"

#define PADDING 2
#define WING_TOP 15
#define WING_WIDTH 25
#define WING_HEIGHT 8
#define COCKPIT_HEIGHT 6
#define NOSE_BOT PADDING + 2
#define COCKPIT_CABIN_SPACING 2
#define CABIN_TOP (PADDING + COCKPIT_HEIGHT)
#define CABIN_HEIGHT 35
#define CABIN_BOT (CABIN_TOP + COCKPIT_CABIN_SPACING + CABIN_HEIGHT)
#define GALLEY_HEIGHT 4
#define BODY_WIDTH 19
#define BODY_HEIGHT (NOSE_BOT + COCKPIT_CABIN_SPACING + CABIN_HEIGHT + GALLEY_HEIGHT)
#define BODY_LEFT (PADDING + WING_WIDTH)
#define BODY_RIGHT (BODY_LEFT + BODY_WIDTH)
#define BODY_BOT (BODY_HEIGHT + NOSE_BOT)
#define TAIL_LENGTH 3

#define SEAT_SPACING_ROW 2
#define SEAT_SPACING_COL 3

void drawWing(Surface* surface, bool right) {
	int offset = 0;

	if (right) {
		offset += BODY_WIDTH + WING_WIDTH + PADDING + 1;
		surface->sdline(offset, WING_TOP, 1, 7, WING_HEIGHT, '\\', '_', SE);
	} else {
		surface->sdline(WING_WIDTH, WING_TOP, 1, 7, WING_HEIGHT, '/', '_', SW);
	}

	surface->hline(offset, WING_TOP + WING_HEIGHT, WING_WIDTH + 1, '-');
}

void drawCockpit(Surface* surface) {
	surface->hline(PADDING + WING_WIDTH + 2, PADDING, BODY_WIDTH / 2, '^');
	surface->set(PADDING + WING_WIDTH + 1, PADDING, '/');
	surface->set(PADDING + WING_WIDTH + 0, PADDING + 1, '/');

	surface->set(PADDING + WING_WIDTH + 5, PADDING, '\\');
	surface->set(PADDING + WING_WIDTH + 6, PADDING + 1, '\\');

	surface->hline(BODY_LEFT, CABIN_TOP, BODY_WIDTH, '-'); // cockpit/cabin separator
}

void drawSeats(Surface* surface) {
	int middle = BODY_WIDTH / 2;
	for (int column = 0; column < BODY_WIDTH; column += SEAT_SPACING_COL) {
		for (int row = 0; row < CABIN_HEIGHT; row += SEAT_SPACING_ROW) {
			if (column == middle) {
				continue;
			} else {
				surface->set(PADDING + WING_WIDTH + column, CABIN_TOP + row + COCKPIT_CABIN_SPACING, '_');
			}
		}
	}
}

void drawTail(Surface* surface) {
	surface->dline(BODY_LEFT, BODY_BOT, BODY_WIDTH / 2, '\\', SE);
	surface->dline(BODY_RIGHT - 1, BODY_BOT, BODY_WIDTH / 2, '/', SW);

	surface->vline(BODY_LEFT + (BODY_WIDTH / 2), BODY_BOT + (BODY_WIDTH / 2), TAIL_LENGTH, '|');
}

void drawBody(Surface* surface) {
	surface->vline(BODY_LEFT - 1, NOSE_BOT, BODY_HEIGHT, '|'); // left side
	surface->vline(BODY_RIGHT, NOSE_BOT, BODY_HEIGHT, '|'); // right side 
}

int main() {
	Surface* surface = new Surface(70, 60, ' ');

	drawBody(surface);
	drawCockpit(surface);

	drawWing(surface, true);
	drawWing(surface, false);

	drawSeats(surface);

	drawTail(surface);

	std::cout << surface->str() << std::endl;
}
