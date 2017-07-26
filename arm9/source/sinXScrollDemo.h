#ifndef SINXSCROLLDEMO_H
#define SINXSCROLLDEMO_H

#include "demo.h"
#include <nds/arm9/background.h>

class SinXScrollDemo : public Demo {
public:
	SinXScrollDemo();
	virtual ~SinXScrollDemo();
	virtual void Load();
	virtual void Unload();
protected:
	void AcceptInput();
	virtual void PrepareFrame(VramBatcher &);

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