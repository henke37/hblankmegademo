#include "demoRunner.h"
#include <nds/arm9/video.h>
#include <nds/interrupts.h>
#include <nds/system.h>

DemoRunner runner;

DemoRunner::DemoRunner() {
}
void DemoRunner::start() {
	irqSet(IRQ_HBLANK, hBlankHandler);
	irqEnable(IRQ_HBLANK);
}
DemoRunner::~DemoRunner() {}

void DemoRunner::hBlankHandler() {
	runner.runCurrentLineFromBatch();
}

void DemoRunner::runCurrentLineFromBatch() {
	int nextLine=REG_VCOUNT+1;
	if(nextLine>=256) return;
	batchers[currentlyRunningBatcher].ApplyPokesForLine(nextLine);
}
