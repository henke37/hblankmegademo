#include "windowingDemo.h"
#include "vrambatcher.h"
#include <nds/arm9/video.h>
#include <nds/arm9/input.h>

#define DARKNESS_MAX 31

WindowingDemo::WindowingDemo() : darkness(DARKNESS_MAX) {}

WindowingDemo::~WindowingDemo() {}

void WindowingDemo::PrepareFrame(VramBatcher &batcher) {
	REG_BLDY = darkness;
}

void WindowingDemo::AcceptInput() {
	auto keys = keysDownRepeat();
	if(keys & KEY_A ) {
		if(darkness>0) darkness--;
	} else if(keys & KEY_B) {
		if(darkness<DARKNESS_MAX) darkness++;
	}
}

void WindowingDemo::Load() {
	setupDefaultBG();
	REG_DISPCNT |= DISPLAY_WIN0_ON;

	WIN_IN = BIT(0);
	WIN_OUT = BIT(0) | BIT(5);
	REG_BLDCNT = BLEND_FADE_BLACK | BLEND_SRC_BG0;

	keysSetRepeat(5, 3);
}
void WindowingDemo::Unload() {
	REG_DISPCNT &= ~DISPLAY_WIN0_ON;
	REG_BLDCNT = BLEND_NONE;
}