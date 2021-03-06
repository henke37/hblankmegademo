#ifndef PEEPHOLEWINDOWDEMO_H
#define PEEPHOLEWINDOWDEMO_H

#include "windowingDemo.h"

#include "fixedMath.h"

#define MIN_HOLE_SIZE 5
#define MAX_HOLE_SIZE 200

class PeepHoleWindowDemo : public WindowingDemo {
public:
	PeepHoleWindowDemo();
	virtual ~PeepHoleWindowDemo();
protected:
	virtual void PrepareFrame(VramBatcher &);
	void AcceptInput();

private:
	/** leftmost edge of the hole */
	fp12 xPos;
	/** top of the hole */
	fp12 yPos;
	/** radius of the hole*/
	fp12 radius;
};

#endif