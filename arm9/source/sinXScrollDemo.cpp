#include "sinXScrollDemo.h"
#include "vrambatcher.h"

SinXScrollDemo::SinXScrollDemo() : amplitude(1), offset(0) {}

void SinXScrollDemo::Load() {}
void SinXScrollDemo::Unload() {}
void SinXScrollDemo::PrepareFrame(VramBatcher &batcher) {
	offset += speed;

	float lineOffset = offset;
	for (int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {
		int xscroll = sin(lineOffset)*amplitude;
		batcher.AddPoke(scanline, xscroll, REG_BG0HOFS);
		lineOffset += lineSpeed;
	}
}