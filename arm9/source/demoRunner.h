#ifndef DEMORUNNER_H
#define DEMORUNNER_H

#include <memory>
#include "vrambatcher.h"

class Demo;

class DemoRunner {
public:
	DemoRunner();
	~DemoRunner();
	void start();

	void RunDemo(std::shared_ptr<Demo>);
	
	void operator=(std::shared_ptr<Demo>);
	
	void tick();
private:
	std::shared_ptr<Demo> demoPtr;
	VramBatcher batcher;
	int currentlyRunningBatcher;
	
	static void hBlankHandler();
	void runCurrentLineFromBatch();
};
extern DemoRunner runner;
#endif