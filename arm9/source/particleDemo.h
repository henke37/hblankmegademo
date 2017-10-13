#ifndef PARTICLE_DEMO_H
#define PARTICLE_DEMO_H

#include "demo.h"

#include <vector>

class BaseParticleDemo : Demo {

public:
	BaseParticleDemo();
	virtual ~BaseParticleDemo();
	virtual void Load();
	virtual void Unload();
protected:
	virtual void PrepareFrame(VramBatcher &)=0;

	struct Particle {
		int x, y;
		int width, height;
		Particle();
		Particle(int x, int y);
		Particle(int x, int y, int width, int height);
	};

private:

	std::vector<Particle> particles;
};

#endif