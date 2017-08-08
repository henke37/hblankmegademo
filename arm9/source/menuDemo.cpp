#include "menuDemo.h"
#include "sinXScrollDemo.h"
#include "peepHoleWindowDemo.h"
#include "spotlightDemo.h"
#include <cassert>

MenuDemo::MenuDemo() {}
MenuDemo::~MenuDemo() {}
void MenuDemo::Load() {
	setupDefaultBG();
}
void MenuDemo::Unload() {}
void MenuDemo::PrepareFrame(VramBatcher &) {


}
void MenuDemo::AcceptInput() {

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
