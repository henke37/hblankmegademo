#ifndef PARTICLE_DEMO_H
#define PARTICLE_DEMO_H

#include "demo.h"

#include <vector>

class ParticleDemo : Demo {

public:
	ParticleDemo();
	virtual ~ParticleDemo();
	virtual void Load();
	virtual void Unload();
protected:
	virtual void PrepareFrame(VramBatcher &);
	void AcceptInput();

private:
	struct Particle {
		int x, y;
		int width, height;
		Particle();
	};

	std::vector<Particle> particles;
	void PrepareLine(int scanline);
};

#endif