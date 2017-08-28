#include "rasterbarDemo.h"
#include "vrambatcher.h"
#include <nds/arm9/background.h>
#include <nds/arm9/video.h>
#include <cstring>

typedef u16 Bgpixels[128][128 / 2];

RasterBarDemo::RasterBarDemo() {}
RasterBarDemo::~RasterBarDemo() {}

void RasterBarDemo::Load() {
	videoSetMode(MODE_3_2D);
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	bgInit(2, BgType_Bmp8, BgSize_B8_128x128, 0, 0);

	u16 *bgPixelsPtr = bgGetGfxPtr(2);
	Bgpixels &bgPixels = *(Bgpixels *)bgPixelsPtr;
	for (int y = 0; y < 128; ++y) {
		for (int x = 0; x < 128; x+=2) {
			bgPixels[y][x / 2] = 0;
		}
	}
}

void RasterBarDemo::Unload() {
}

void RasterBarDemo::AcceptInput() {
}

void RasterBarDemo::PrepareFrame(VramBatcher & batcher) {
	u16 lineColors[SCREEN_HEIGHT] = {
		RGB5(0,0,0)
	};

	for (int y = 30; y < 50; ++y) {
		lineColors[80-(y-19)]=lineColors[y] = RGB5(y - 30, 0, 0);
	}

	for (int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {
		batcher.AddPoke(scanline, lineColors[scanline], &BG_PALETTE[0]);
	}
}
