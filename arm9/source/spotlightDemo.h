#ifndef SPOTLIGHTDEMO_H
#define SPOTLIGHTDEMO_H

#include "windowingDemo.h"

class SpotLightDemo : public WindowingDemo {
public:
	SpotLightDemo();
	virtual ~SpotLightDemo();
protected:
	virtual void PrepareFrame(VramBatcher &);
	virtual void AcceptInput();

private:
	/** The x position of the light */
	int lightX;
	/** The y position of the light */
	int lightY;
	/** The direction of the light, in radians */
	float angle;
	/** The spread angle of the light, in radians */
	float spread;
};

#endif