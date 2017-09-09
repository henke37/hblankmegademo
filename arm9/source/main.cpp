#include <nds.h>
#include <filesystem.h>
#include <nds/arm9/console.h>

#include "demo.h"
#include "demoRunner.h"
#include "menuDemo.h"
#include "rasterbarDemo.h"

void testFixed();

int main(void) {

	char **basePath=nullptr;

	nitroFSInit(basePath);


	consoleDemoInit();


	runner=std::make_shared<MenuDemo>();

	irqEnable(IRQ_VBLANK);


	testFixed();

	for(;;) {
		swiWaitForVBlank();
		scanKeys();
		runner.tick();
	}
}
