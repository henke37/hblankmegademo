#include "superParallaxDemo.h"
#include "vrambatcher.h"
#include <nds/arm9/background.h>
#include <nds/arm9/video.h>
#include <cmath>

SuperParallaxDemo::SuperParallaxDemo() {}
SuperParallaxDemo::~SuperParallaxDemo() {}
void SuperParallaxDemo::Load() {}
void SuperParallaxDemo::Unload() {}


BgPointerRecord BgPointers[4] = {
	{ &REG_BG0HOFS, &REG_BG0VOFS, &REG_BG0CNT, {0} },
	{ &REG_BG1HOFS, &REG_BG1VOFS, &REG_BG1CNT, {0} },
	{ &REG_BG2HOFS, &REG_BG2VOFS, &REG_BG2CNT, { &REG_BG2PA, &REG_BG2PB, &REG_BG2PC, &REG_BG2PD, &REG_BG2X, &REG_BG2Y } },
	{ &REG_BG3HOFS, &REG_BG3VOFS, &REG_BG3CNT, { &REG_BG3PA, &REG_BG3PB, &REG_BG3PC, &REG_BG3PD, &REG_BG3X, &REG_BG3Y } }
};

void SuperParallaxDemo::PrepareFrame(VramBatcher &batcher) {

	//tick _all_ regions
	for (auto itr = regions.begin(); itr < regions.end(); ++itr) {
		itr->tick();
	}


	for (int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {
		//find topmost two regions that have the lowest depth
		ParallaxRegion *low=nullptr, *lower=nullptr;
		for (auto itr = regions.begin(); itr < regions.end(); ++itr) {
			if (!low) {
				low = &*itr;
			} else if (!lower) {
				if (low->depth >= itr->depth) {
					lower = &*itr;
				} else {
					lower = low;
					low = &*itr;
				}
			} else {
				if (lower->depth >= itr->depth) {
					low = lower;
					lower = &*itr;
				} else if (low->depth >= itr->depth) {
					low = &*itr;
				}
			}
		}

		//ensure that used layers, and only used layers, are visible
		batcher.AddPoke(
			scanline,
			(lower?DISPLAY_BG0_ACTIVE:0)|(low? DISPLAY_BG1_ACTIVE :0),
			0x30,
			&REG_DISPCNT
		);

		if (lower) lower->applyForScanline(scanline, BgPointers[0], xPos, yPos, batcher);
		if (low) low->applyForScanline(scanline, BgPointers[1], xPos, yPos, batcher);
	}
	 
}

SuperParallaxDemo::ParallaxRegion::ParallaxRegion() {
}

SuperParallaxDemo::ParallaxRegion::~ParallaxRegion() {
}

void SuperParallaxDemo::ParallaxRegion::tick() {
	wobblePhase += wobbleRate;
}

void SuperParallaxDemo::ParallaxRegion::applyForScanline(int scanline, BgPointerRecord &bgPtrs, int xPos, int yPos, VramBatcher &batcher) {
	//ensure that the map pointer is set
	batcher.AddPoke(scanline, mapBase << 8, 0x1F00, bgPtrs.bgcnt);
	//ensure that the palette is set
	//compute the scroll Y position for the line
	int layerYOffset = top - (scanline - yPos);
	batcher.AddPoke(scanline, layerYOffset, bgPtrs.vOffset);
	//compute the base scroll X position for the region
	int layerXOffset = xPos*scrollRate;
	//add in the modulation
	layerXOffset += sin(wobblePhase + layerYOffset*wobbleLinePhase)*wobbleAmplitude;
	batcher.AddPoke(scanline, layerXOffset, bgPtrs.hOffset);
}
