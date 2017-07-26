#include "sinXScrollDemo.h"
#include "vrambatcher.h"
#include <cmath>

SinXScrollDemo::SinXScrollDemo() : offset(0), amplitude(1) {}

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