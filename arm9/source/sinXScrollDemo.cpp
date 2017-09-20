#include "sinXScrollDemo.h"
#include "vrambatcher.h"
#include <cmath>
#include <nds/arm9/input.h>
#include <nds/arm9/background.h>

#define MIN_AMPLITUDE 0_fp12
#define MAX_AMPLITUDE 256_fp12
#define MAX_SPEED 5000_fixedAngle
#define MIN_SPEED 0_fixedAngle
#define MAX_LINESPEED 5000_fixedAngle
#define MIN_LINESPEED 0_fixedAngle

SinXScrollDemo::SinXScrollDemo() : offset(0), speed(200), amplitude(15), lineSpeed(60) {}
SinXScrollDemo::~SinXScrollDemo() {}

void SinXScrollDemo::AcceptInput() {
	auto keys = keysDownRepeat();
	if(keys & KEY_X && amplitude > MIN_AMPLITUDE) {
		amplitude -= 1;
	} else if(keys & KEY_Y && amplitude < MAX_AMPLITUDE) {
		amplitude += 1;
	}

	if(keys & KEY_UP && speed < MAX_SPEED) {
		speed += 10;
	} else if(keys & KEY_DOWN && speed > MIN_SPEED) {
		speed -= 10;
	}

	if(keys & KEY_LEFT && lineSpeed > MIN_LINESPEED) {
		lineSpeed -= 5;
	} else if(keys & KEY_RIGHT && lineSpeed < MAX_LINESPEED) {
		lineSpeed += 5;
	}
}

void SinXScrollDemo::Load() {
	setupDefaultBG();
	keysSetRepeat(15, 5);
}
void SinXScrollDemo::Unload() {}
void SinXScrollDemo::PrepareFrame(VramBatcher &batcher) {
	offset += speed;

	FixedAngle lineOffset = offset;
	for (int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {
		fp12 xscroll = sin(lineOffset)*amplitude;
		batcher.AddPoke(scanline, (int16_t)(int)xscroll, &REG_BG0HOFS);

		lineOffset += lineSpeed;
	}
}