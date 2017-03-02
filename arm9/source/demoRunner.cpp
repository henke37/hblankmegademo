#include "demoRunner.h"
#include <nds/arm9/video.h>
#include <nds/interrupts.h>
#include <nds/system.h>

#include "demo.h"

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
	batcher.Clear();
	demoPtr->PrepareFrame(batcher);
	batcher.ApplyPokesForLine(0);
}

void DemoRunner::operator=(std::shared_ptr<Demo> d) {
	RunDemo(d);
}


void DemoRunner::RunDemo(std::shared_ptr<Demo> d) {
	if(demoPtr) {
		demoPtr->Unload();
		if(!d) stop();
	}
	demoPtr=d;
	if(!d) return;
	
	demoPtr->Load();
	start();
}