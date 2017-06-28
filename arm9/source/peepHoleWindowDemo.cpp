#include "peepHoleWindowDemo.h"
#include "vrambatcher.h"
#include <cmath>

PeepHoleWindowDemo::PeepHoleWindowDemo() {}
PeepHoleWindowDemo::~PeepHoleWindowDemo() {}
void PeepHoleWindowDemo::Load() {}
void PeepHoleWindowDemo::Unload() {}

void PeepHoleWindowDemo::PrepareFrame(VramBatcher &batcher) {
	int scanline = 0;
	//turn everything off until the first line of the hole
	if (yPos > 0) {

	}

	int height = radius * 2;

	//jump to the top of the hole
	scanline = yPos;
	//turn on windowing and set windowing

	//start generating the hole
	for (; scanline < yPos + height && scanline < SCREEN_HEIGHT; ++scanline) {
		float angle = std::asin((radius - (scanline - yPos)) / radius);
		int width=std::cos(angle)*radius*2;
		int left=xPos+width/2;
		int right=left+width;
		batcher.AddPoke(scanline, left, &WIN0_X0);
		batcher.AddPoke(scanline, right, &WIN0_X1);
	}

	//turn everything off again
	if (scanline < SCREEN_HEIGHT) {

	}
}