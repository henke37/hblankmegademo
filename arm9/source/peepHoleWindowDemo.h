#ifndef PEEPHOLEWINDOWDEMO_H
#define PEEPHOLEWINDOWDEMO_H

#include "demo.h"

class PeepHoleWindowDemo : public Demo {
public:
	PeepHoleWindowDemo();
	virtual ~PeepHoleWindowDemo();
	virtual void PrepareFrame(VramBatcher &);
	virtual void Load();
	virtual void Unload();

private:
	/** top of the hole */
	int yPos;
	/** leftmost edge of the hole */
	int xPos;
	/** radius of the hole*/
	float radius;
};

#endif