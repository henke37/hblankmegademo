#include "superParallaxDemo.h"
#include "vrambatcher.h"

SuperParallaxDemo::SuperParallaxDemo() {}
SuperParallaxDemo::~SuperParallaxDemo() {}
void SuperParallaxDemo::Load() {}
void SuperParallaxDemo::Unload() {}

struct BgPointerRecord {
	vu16* hOffset;
	vu16* vOffset;
	vu16* bgcnt;
} BgPointers[4] = {
	{ REG_BG0HOFS, REG_BG0VOFS, REG_BG0CNT },
	{ REG_BG1HOFS, REG_BG1VOFS, REG_BG1CNT },
	{ REG_BG2HOFS, REG_BG2VOFS, REG_BG2CNT },
	{ REG_BG3HOFS, REG_BG3VOFS, REG_BG3CNT }
};

void SuperParallaxDemo::PrepareFrame(VramBatcher &batcher) {

	//tick _all_ regions
	for (auto itr = regions.begin(); itr < regions.end(); ++itr) {
		itr->tick();
	}


	for (int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {
		//find topmost two regions that have the lowest depth
		ParallaxRegion *low, *lower;
		for (auto itr = regions.begin(); itr < regions.end(); ++itr) {
			if (!low) {
				low = itr._Ptr;
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

		if (lower) lower->applyForScanline(scanline,xPos,yPos,batcher);
		if (low) low->applyForScanline(scanline, xPos, yPos, batcher);
	}
	 
}

SuperParallaxDemo::ParallaxRegion::ParallaxRegion() {
}

SuperParallaxDemo::ParallaxRegion::~ParallaxRegion() {
}

void SuperParallaxDemo::ParallaxRegion::tick() {
	wobblePhase += wobbleRate;
}

void SuperParallaxDemo::ParallaxRegion::applyForScanline(int scanline, int xPos, int yPos, VramBatcher &batcher) {
	//determinate the background layer to use
	BgPointerRecord bgPtrs;
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
