#include <nds.h>
#include <filesystem.h>
#include "demo.h"
#include "demoRunner.h"
#include "menuDemo.h"

int main(void) {

	char **basePath=nullptr;

	nitroFSInit(basePath);

	runner=std::make_shared<MenuDemo>();
	runner.start();
	for(;;) {
		swiWaitForVBlank();
		runner.tick();
	}
}
