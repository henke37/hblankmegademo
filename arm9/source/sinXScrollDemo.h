#ifndef SINXSCROLLDEMO_H
#define SINXSCROLLDEMO_H

#include "demo.h"

class SinXScrollDemo : public Demo {
public:
	SinXScrollDemo();
	virtual ~SinXScrollDemo();
	virtual void PrepareFrame(VramBatcher &);
	virtual void Load();
	virtual void Unload();

private:
	/** Current scroll base*/
	float offset;
	/** speed of scroll base*/
	float speed;
	/** strength of modulation*/
	float amplitude;
	/** modulation offset per line*/
	float lineSpeed;
};

#endif