#include <nds.h>
#include "demo.h"
#include "demoRunner.h"
#include "menuDemo.h"

int main(void) {

	runner=std::make_shared<MenuDemo>();
	
	for(;;) {
		swiWaitForVBlank();
		runner.tick();
	}
}
