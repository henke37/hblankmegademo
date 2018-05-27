#include "demoRunner.h"
#include "objectManager.h"
#include <nds/arm9/video.h>
#include <nds/system.h>

#ifdef __INTELLISENSE__
#undef ITCM_CODE
#define ITCM_CODE
#endif

VramBatcher batchers[NUM_BATCHERS];

ITCM_CODE void DemoRunner::hBlankHandler() {
	runner.runCurrentLineFromBatch();

	if(!(REG_DISPSTAT & DISP_IN_HBLANK)) {
		fprintf(stderr, "HBlank handler overshot for line %d!", REG_VCOUNT);
	}

	mainObjManager.setupNextHDMA();
	subObjManager.setupNextHDMA();
}

ITCM_CODE void DemoRunner::runCurrentLineFromBatch() {
	int nextLine = REG_VCOUNT + 1;
	if(nextLine >= SCREEN_HEIGHT) return;
	batchers[currentlyRunningBatcher].ApplyPokesForLine(nextLine);
}