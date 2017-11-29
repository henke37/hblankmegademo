#include <nds.h>
#include <filesystem.h>
#include <nds/arm9/console.h>

#include "demo.h"
#include "demoRunner.h"
#include "menuDemo.h"
#include "rasterbarDemo.h"
#include "objectManager.h"

#include <cstdio>

void testFixed();
void onVBlank();

volatile unsigned long int currentFrame = 0;

int main(void) {

	char **basePath=nullptr;

	nitroFSInit(basePath);


	consoleDemoInit();


	runner=std::make_shared<MenuDemo>();

	irqEnable(IRQ_VBLANK);


	testFixed();

	irqSet(IRQ_VBLANK, onVBlank);


	for(;;) {
		swiWaitForVBlank();

		long unsigned int thisFrame = currentFrame;

		scanKeys();
		runner.tick();
		mainObjManager.tick();

		if(thisFrame != currentFrame) {
			printf("Vblank overrun! %lu %lu\n",thisFrame,currentFrame);
		}
	}
}

void onVBlank() {
	++currentFrame;
}