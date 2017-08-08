#include "sinXScrollDemo.h"
#include "vrambatcher.h"
#include <cmath>
#include <nds/arm9/input.h>

#define MIN_AMPLITUDE 0
#define MAX_AMPLITUDE 256
#define MAX_SPEED 0.2
#define MIN_SPEED 0
#define MAX_LINESPEED 0.2
#define MIN_LINESPEED 0

SinXScrollDemo::SinXScrollDemo() : offset(0), amplitude(1) {}
SinXScrollDemo::~SinXScrollDemo() {}

void SinXScrollDemo::AcceptInput() {
	auto keys = keysCurrent();
	if(keys & KEY_X && amplitude > MIN_AMPLITUDE) {
		amplitude -= 0.01;
	} else if(keys & KEY_Y && amplitude < MAX_AMPLITUDE) {
		amplitude += 0.01;
	}

	if(keys & KEY_UP && speed < MAX_SPEED) {
		speed += 0.01;
	} else if(keys & KEY_DOWN && speed > MIN_SPEED) {
		speed -= 0.01;
	}

	if(keys & KEY_LEFT && lineSpeed > MIN_LINESPEED) {
		lineSpeed -= 0.01;
	} else if(keys & KEY_RIGHT && lineSpeed < MAX_LINESPEED) {
		lineSpeed += 0.01;
	}
}

void SinXScrollDemo::Load() {
	setupDefaultBG();
}
void SinXScrollDemo::Unload() {}
void SinXScrollDemo::PrepareFrame(VramBatcher &batcher) {
	offset += speed;

	float lineOffset = offset;
	for (int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {
		int xscroll = std::sin(lineOffset)*amplitude;
		batcher.AddPoke(scanline, xscroll, &REG_BG0HOFS);
		lineOffset += lineSpeed;
	}
}