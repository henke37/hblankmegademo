#include "particleDemo.h"
#include "vrambatcher.h"
#include <nds/arm9/video.h>
#include <nds/arm9/sprite.h>

ParticleDemo::ParticleDemo() {}
ParticleDemo::~ParticleDemo() {}
void ParticleDemo::Load() {
	REG_DISPCNT = DISPLAY_SPR_ACTIVE | DISPLAY_SPR_HBLANK;
}

void ParticleDemo::Unload() {}

void ParticleDemo::PrepareFrame(VramBatcher &batcher) {
	for(int scanline = 0; scanline < SCREEN_HEIGHT; ++scanline) {
		
	}
}

void ParticleDemo::PrepareLine(int scanline) {
	int oamSlot = 0;
	for(auto &particle : particles) {
		if(particle.y > scanline) continue;
		if(particle.y + particle.height < scanline) continue;

		//TODO: move the updates to hblank
		auto &slot = oamMain.oamMemory[oamSlot];

		slot.x = particle.x;
		slot.y = particle.y;
		slot.isHidden = 0;
	}

	for(; oamSlot < SPRITE_COUNT; ++oamSlot) {
		//TODO: move to hblank
		auto &slot = oamMain.oamMemory[oamSlot];
		slot.isHidden = 0;
	}
}