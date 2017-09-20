#ifndef SINXSCROLLDEMO_H
#define SINXSCROLLDEMO_H

#include "demo.h"
#include "fixedMath.h"

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
	FixedAngle offset;
	/** speed of scroll base*/
	FixedAngle speed;
	/** strength of modulation*/
	fp12 amplitude;
	/** modulation offset per line*/
	FixedAngle lineSpeed;
};

#endif