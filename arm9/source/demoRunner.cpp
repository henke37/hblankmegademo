#include "demoRunner.h"
#include <nds/arm9/video.h>
#include <nds/interrupts.h>
#include <nds/system.h>
#include <nds/arm9/input.h>

#include "demo.h"
#include "menuDemo.h"

DemoRunner runner;

DemoRunner::DemoRunner() {
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

void DemoRunner::hBlankHandler() {
	runner.runCurrentLineFromBatch();
}

void DemoRunner::runCurrentLineFromBatch() {
	int nextLine=REG_VCOUNT+1;
	if(nextLine>=SCREEN_HEIGHT) return;
	batcher.ApplyPokesForLine(nextLine);
}

void DemoRunner::tick() {
	//get an extra refrence to avoid pulling the rug from underneath
	//the current demo when switching demo
	auto demoToRun = demoPtr;

	auto keys = keysDown();
	batcher.Clear();
	if(keys & KEY_SELECT) {
		RunDemo(std::make_shared<MenuDemo>());
	}
	demoToRun->tick();

	batcher.ApplyPokesForLine(0);
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