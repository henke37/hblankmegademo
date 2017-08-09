#include <nds.h>
#include <filesystem.h>
#include "demo.h"
#include "demoRunner.h"
#include "menuDemo.h"
#include "spotlightDemo.h"

int main(void) {

	char **basePath=nullptr;

	nitroFSInit(basePath);


	runner=std::make_shared<SpotLightDemo>();
	runner.start();

	irqEnable(IRQ_VBLANK);

	for(;;) {
		swiWaitForVBlank();
		scanKeys();
		runner.tick();
	}
}
