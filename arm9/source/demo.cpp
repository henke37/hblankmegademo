#include "demo.h"
#include "demoRunner.h"

Demo::Demo() {}
Demo::~Demo() {}

void Demo::tick() {
	AcceptInput();
	PrepareFrame(runner.batcher);
}

void Demo::setupDefaultBG() {
}
