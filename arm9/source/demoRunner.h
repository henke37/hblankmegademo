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
private:
	std::shared_ptr<Demo> demoPtr;
	VramBatcher batchers[2];
	int currentlyRunningBatcher;
	
	static void hBlankHandler();
	void runCurrentLineFromBatch();
};
extern DemoRunner runner;
#endif