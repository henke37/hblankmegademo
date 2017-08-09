#ifndef PEEPHOLEWINDOWDEMO_H
#define PEEPHOLEWINDOWDEMO_H

#include "demo.h"

#define MIN_HOLE_SIZE 5
#define MAX_HOLE_SIZE 200

class PeepHoleWindowDemo : public Demo {
public:
	PeepHoleWindowDemo();
	virtual ~PeepHoleWindowDemo();
	virtual void Load();
	virtual void Unload();
protected:
	virtual void PrepareFrame(VramBatcher &);
	void AcceptInput();

private:
	/** leftmost edge of the hole */
	int xPos;
	/** top of the hole */
	int yPos;
	/** radius of the hole*/
	float radius;
};

#endif