#include "menuDemo.h"
#include "sinXScrollDemo.h"
#include "peepHoleWindowDemo.h"
#include "spotlightDemo.h"
#include "demoRunner.h"

#include <cassert>
#include <nds/arm9/input.h>

MenuDemo::MenuDemo() {}
MenuDemo::~MenuDemo() {}
void MenuDemo::Load() {
	setupDefaultBG();
}
void MenuDemo::Unload() {}
void MenuDemo::PrepareFrame(VramBatcher &) {


}
void MenuDemo::AcceptInput() {
	auto keys = keysDown();

	if(keys & KEY_UP && selection > 0) {
		selection--;
	} else if(keys & KEY_DOWN && selection+1 < demoCount) {
		selection++;
	}

	if(keys & KEY_START) {
		runner.RunDemo(makeDemo());
	}
}

std::shared_ptr<Demo> MenuDemo::makeDemo() {
	switch(selection) {
	case 0:
		return std::make_shared<SinXScrollDemo>();
	case 1:
		return std::make_shared<SpotLightDemo>();
	case 2:
		return std::make_shared<PeepHoleWindowDemo>();
	}
	assert(0);
}
