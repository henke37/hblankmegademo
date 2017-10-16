#ifndef FLUTTER_DEMO_H
#define FLUTTER_DEMO_H

#include "particledemo.h"

class FlutterDemo : public BaseParticleDemo {
	FlutterDemo();
	virtual ~FlutterDemo();
	virtual void Load();
	virtual void Unload();
protected:
	virtual void PrepareFrame(VramBatcher &);
private:
	void setupParticles();
	void loadGraphics();
};

#endif