#include "scanInDemo.h"
#include "vrambatcher.h"

#include <nds/arm9/input.h>
#include <nds/arm9/video.h>
#include <nds/arm9/background.h>

ScanInDemo::ScanInDemo() : startLine(64) {}
ScanInDemo::~ScanInDemo() {}

void ScanInDemo::Load() {
	setupDefaultBG();
	keysSetRepeat(5, 2);
}
void ScanInDemo::Unload() {

}

void ScanInDemo::AcceptInput() {
	auto keys = keysDownRepeat();
	if (startLine > 0 && keys & KEY_UP) {
		startLine--;
	} else if (startLine < SCREEN_HEIGHT && keys & KEY_DOWN) {
		startLine++;
	}
}

void ScanInDemo::PrepareFrame(VramBatcher &batcher) {
	if (startLine != 0) {
		batcher.AddPoke(0, 0, &REG_BG0VOFS);
	}

	for (int scanline = startLine + 1; scanline < SCREEN_HEIGHT; ++scanline) {
		int scroll = startLine - scanline;
		batcher.AddPoke(scanline, scroll, &REG_BG0VOFS);
	}
}
