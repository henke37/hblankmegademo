#include "demoRunner.h"
#include <nds/arm9/video.h>
#include <nds/interrupts.h>
#include <nds/system.h>
#include <nds/arm9/input.h>

#include "demo.h"
#include "menuDemo.h"

#include <cstdio>
#include <cstdlib>

DemoRunner runner;

DemoRunner::DemoRunner() : currentlyRunningBatcher(0) {
}
void DemoRunner::start() {
	irqSet(IRQ_HBLANK, hBlankHandler);
	irqEnable(IRQ_HBLANK);
}
void DemoRunner::stop() {
	irqDisable(IRQ_HBLANK);
}
DemoRunner::~DemoRunner() {
	if(demoPtr) {
		demoPtr->Unload();
	}
	stop();
}

void DemoRunner::tick() {
	//get an extra refrence to avoid pulling the rug from underneath
	//the current demo when switching demo
	auto demoToRun = demoPtr;

	auto &backBatcher = batchers[currentlyRunningBatcher];
	currentlyRunningBatcher = (currentlyRunningBatcher + 1) % NUM_BATCHERS;
	auto &frontBatcher = batchers[currentlyRunningBatcher];

	frontBatcher.ApplyPokesForLine(0);

	auto keys = keysDown();
	backBatcher.Clear();
	if(keys & KEY_SELECT) {
		RunDemo(std::make_shared<MenuDemo>());
	}
	demoToRun->tick(backBatcher);
}

void DemoRunner::operator=(std::shared_ptr<Demo> d) {
	RunDemo(d);
}


void DemoRunner::RunDemo(std::shared_ptr<Demo> d) {
	if(demoPtr) {
		demoPtr->Unload();
	}
	if(!d) {
		stop();
		demoPtr = d;
		return;
	}
	if(!demoPtr) start();
	
	d->Load();

	demoPtr = d;
}