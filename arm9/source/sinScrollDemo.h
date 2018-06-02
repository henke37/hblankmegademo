#ifndef SINXSCROLLDEMO_H
#define SINXSCROLLDEMO_H

#include "demo.h"
#include "fixedMath.h"

class SinScrollDemo : public Demo {
public:
	SinScrollDemo();
	virtual ~SinScrollDemo();
	virtual void Load();
protected:
	void AcceptInput();

protected:
	/** Current scroll base*/
	FixedAngle offset;
	/** speed of scroll base*/
	FixedAngle speed;
	/** strength of modulation*/
	fp12 amplitude;
	/** modulation offset per line*/
	FixedAngle lineSpeed;
};

class SinXScrollDemo : public SinScrollDemo {
public:
	virtual void PrepareFrame(VramBatcher &);
	virtual void Unload();
};

class SinYScrollDemo : public SinScrollDemo {
public:
	virtual void PrepareFrame(VramBatcher &);
	virtual void Unload();
};


#endif