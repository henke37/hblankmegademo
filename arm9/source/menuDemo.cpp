#include "menuDemo.h"
#include "sinScrollDemo.h"
#include "peepHoleWindowDemo.h"
#include "spotlightDemo.h"
#include "demoRunner.h"
#include "scanInDemo.h"
#include "rasterbarDemo.h"
#include "flutterDemo.h"

#include <cassert>
#include <nds/arm9/input.h>

MenuDemo::MenuDemo() : selection(0) {}
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
	case 3:
		return std::make_shared<ScanInDemo>();
	case 4:
		return std::make_shared<RasterBarDemo>();
	case 5:
		return std::make_shared<FlutterDemo>();
	case 6:
		return std::make_shared<SinYScrollDemo>();
	}
	sassert(0,"Bad menu selection instatiated");

	assert(0);
}
