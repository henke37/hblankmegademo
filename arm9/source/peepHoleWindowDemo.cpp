#include "peepHoleWindowDemo.h"
#include "vrambatcher.h"
#include <cmath>
#include <nds/arm9/input.h>

PeepHoleWindowDemo::PeepHoleWindowDemo() : xPos(128), yPos(64-25), radius(50) {}
PeepHoleWindowDemo::~PeepHoleWindowDemo() {}

void PeepHoleWindowDemo::Load() {
	setupDefaultBG();
	WIN_IN = BIT(0);
	WIN_OUT = 0;

	REG_DISPCNT |= DISPLAY_WIN0_ON | DISPLAY_BG0_ACTIVE;
}
void PeepHoleWindowDemo::Unload() {
	REG_DISPCNT &= ~DISPLAY_WIN0_ON;
}

void PeepHoleWindowDemo::AcceptInput() {
	auto keys = keysCurrent();
	if(keys & KEY_X && this->radius > MIN_HOLE_SIZE) {
		radius -= 0.1;
	} else if(keys & KEY_Y && radius < MAX_HOLE_SIZE) {
		radius += 0.1;
	}

	if(keys & KEY_LEFT && xPos > -radius) {
		xPos--;
	} else if(keys & KEY_RIGHT && xPos < SCREEN_WIDTH+radius) {
		xPos++;
	}

	if(keys & KEY_UP && yPos > -radius) {
		yPos--;
	} else if(keys& KEY_DOWN && yPos < SCREEN_HEIGHT) {
		yPos++;
	}
}

void PeepHoleWindowDemo::PrepareFrame(VramBatcher &batcher) {
	int height = radius * 2;

	int bottom;
	int top;

	//cap top and bottom to visible part if mostly off the left side of the screen
	if(xPos < 0) {
		int halfVisibleHeight = std::sqrt(radius*radius - xPos*xPos);
		top = yPos + radius - halfVisibleHeight;
		bottom = top + 2 * halfVisibleHeight;
	} else if(xPos > SCREEN_WIDTH) {
		int circleIntersectionX = xPos - SCREEN_WIDTH;
		int halfVisibleHeight = std::sqrt(radius*radius - circleIntersectionX*circleIntersectionX);
		top = yPos + radius - halfVisibleHeight;
		bottom = top + 2 * halfVisibleHeight;
	} else {
		//basic top and bottom
		bottom = yPos + height;
		top = yPos;
	}

	//cap top and bottom to the screen area
	if(top < 0) top = 0;
	if(bottom > SCREEN_HEIGHT) bottom = SCREEN_HEIGHT;

	batcher.AddPoke(0, top, &WIN0_Y0);
	batcher.AddPoke(0, bottom, &WIN0_Y1);

	//start generating the hole
	for (int scanline = top; scanline < bottom; ++scanline) {
		float angle = std::asin((radius - (scanline - yPos)) / radius);
		int width=std::cos(angle)*radius*2;
		int left=xPos-width/2;
		int right=left+width;

		if(left < 0) left = 0;
		if(right > SCREEN_WIDTH) right = SCREEN_WIDTH;

		batcher.AddPoke(scanline, left, &WIN0_X0);
		batcher.AddPoke(scanline, right, &WIN0_X1);
	}
}