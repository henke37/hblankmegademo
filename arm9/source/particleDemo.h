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

	void buildObjectsFromParticles();

	struct Particle {
		int x, y;
		int width, height;
		int baseTile;
		int palette;
		Particle();
		Particle(int x, int y, int baseTile, int palette = 0);
		Particle(int x, int y, int width, int height, int baseTile, int palette=0);
	};

	std::vector<Particle> particles;

private:

};

#endif