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
#define M_PI       3.14159265358979323846

SinXScrollDemo::SinXScrollDemo() : offset(0), speed(0.1), amplitude(10), lineSpeed(0.01) {}
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
	if(offset > M_PI*2) offset -= M_PI*2;

	float lineOffset = offset;
	for (int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {
		int xscroll = std::sin(lineOffset)*amplitude;
		batcher.AddPoke(scanline, xscroll, &REG_BG0HOFS);
		lineOffset += lineSpeed;
	}
}