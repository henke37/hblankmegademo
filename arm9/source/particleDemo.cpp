#include "particleDemo.h"
#include "vrambatcher.h"
#include <nds/arm9/video.h>

ParticleDemo::ParticleDemo() {}
ParticleDemo::~ParticleDemo() {}
void ParticleDemo::Load() {
	REG_DISPCNT = DISPLAY_SPR_ACTIVE;
}

void ParticleDemo::Unload() {}

void ParticleDemo::PrepareFrame(VramBatcher &batcher) {
	for(int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {
		std::vector<Particle *> particlesForLine;
		for(auto &particle : particles) {
			if(particle.y > scanline) continue;
			if(particle.y + particle.height < scanline) continue;
			particlesForLine.push_back(&particle);
		}
	}
}