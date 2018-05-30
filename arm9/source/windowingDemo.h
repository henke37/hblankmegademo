#ifndef WINDOWING_DEMO_H
#define WINDOWING_DEMO_H

#include "demo.h"

class WindowingDemo : public HBlankDemo {
public:
	virtual ~WindowingDemo();

	virtual void PrepareFrame(VramBatcher &);
	virtual void AcceptInput();

	virtual void Load();
	virtual void Unload();

protected:

};

#endif