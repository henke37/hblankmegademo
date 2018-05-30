#include "windowingDemo.h"
#include <nds/arm9/video.h>
#include <nds/arm9/window.h>

WindowingDemo::~WindowingDemo() {}

void WindowingDemo::PrepareFrame(VramBatcher &) {}

void WindowingDemo::AcceptInput() {}

void WindowingDemo::Load() {
	setupDefaultBG();
	REG_DISPCNT |= DISPLAY_WIN0_ON;

	WIN_IN = BIT(0);
	WIN_OUT = 0;
}
void WindowingDemo::Unload() {
	REG_DISPCNT &= ~DISPLAY_WIN0_ON;
}