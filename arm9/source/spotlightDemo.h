#ifndef SPOTLIGHTDEMO_H
#define SPOTLIGHTDEMO_H

#include "demo.h"

class SpotLightDemo : public Demo {
public:
	SpotLightDemo();
	virtual ~SpotLightDemo();
	virtual void PrepareFrame(VramBatcher &);
	virtual void Load();
	virtual void Unload();

private:
	/** The x position of the light */
	int lightX;
	/** The y position of the light */
	int lightY;
	/** The angle of the light, in radians */
	float angle;
	/** The spread of the light, in radians */
	float spread;
};

#endif