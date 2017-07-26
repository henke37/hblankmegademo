#include "peepHoleWindowDemo.h"
#include "vrambatcher.h"
#include <cmath>
#include <nds/arm9/input.h>

PeepHoleWindowDemo::PeepHoleWindowDemo() {}
PeepHoleWindowDemo::~PeepHoleWindowDemo() {}

void PeepHoleWindowDemo::Load() {
	setupDefaultBG();
}
void PeepHoleWindowDemo::Unload() {
	REG_DISPCNT &= ~DISPLAY_WIN0_ON;
}

void PeepHoleWindowDemo::AcceptInput() {
	auto keys = keysCurrent();
	if(keys & KEY_X && this->radius > MIN_HOLE_SIZE) {
		radius -= 0.01;
	} else if(keys & KEY_Y && radius < MAX_HOLE_SIZE) {
		radius += 0.01;
	}

	if(keys & KEY_LEFT && xPos > 0) {
		xPos--;
	} else if(keys & KEY_RIGHT && xPos < SCREEN_WIDTH) {
		xPos++;
	}

	if(keys & KEY_UP && yPos > 0) {
		yPos--;
	} else if(keys& KEY_DOWN && yPos < SCREEN_HEIGHT) {
		yPos++;
	}
}

void PeepHoleWindowDemo::PrepareFrame(VramBatcher &batcher) {
	int scanline = 0;
	//turn everything off until the first line of the hole
	if (yPos > 0) {
		batcher.AddPoke(scanline, 0, DISPLAY_WIN0_ON | DISPLAY_BG0_ACTIVE, &REG_DISPCNT);
	}

	int height = radius * 2;

	//jump to the top of the hole
	scanline = yPos;
	//turn on windowing and set windowing
	batcher.AddPoke(scanline, DISPLAY_WIN0_ON| DISPLAY_BG0_ACTIVE, DISPLAY_WIN0_ON| DISPLAY_BG0_ACTIVE, &REG_DISPCNT);

	//start generating the hole
	for (; scanline < yPos + height && scanline < SCREEN_HEIGHT; ++scanline) {
		float angle = std::asin((radius - (scanline - yPos)) / radius);
		int width=std::cos(angle)*radius*2;
		int left=xPos-width/2;
		int right=left+width;

		if(left < 0) left = 0;
		if(right > SCREEN_WIDTH) right = SCREEN_WIDTH;

		batcher.AddPoke(scanline, left, &WIN0_X0);
		batcher.AddPoke(scanline, right, &WIN0_X1);
	}

	//turn everything off again
	if (scanline < SCREEN_HEIGHT) {
		batcher.AddPoke(scanline, 0, DISPLAY_WIN0_ON | DISPLAY_BG0_ACTIVE, &REG_DISPCNT);
	}
}