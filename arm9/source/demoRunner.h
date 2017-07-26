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
	void stop();

	void RunDemo(std::shared_ptr<Demo>);
	
	void operator=(std::shared_ptr<Demo>);
	
	void tick();

	VramBatcher batcher;
private:
	std::shared_ptr<Demo> demoPtr;
	int currentlyRunningBatcher;
	
	static void hBlankHandler();
	void runCurrentLineFromBatch();
};
extern DemoRunner runner;
#endif